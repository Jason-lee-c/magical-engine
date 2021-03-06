﻿/******************************************************************************
The MIT License (MIT)

Copyright (c) 2014 Jason.lee

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*******************************************************************************/
#include "c-plane.h"

cBool magicalPlaneEquals( const cPlane* p1, const cPlane* p2 )
{
	return
		magicalAlmostEqual( p1->x, p2->x, kVectorEpsilon ) &&
		magicalAlmostEqual( p1->y, p2->y, kVectorEpsilon ) &&
		magicalAlmostEqual( p1->z, p2->z, kVectorEpsilon ) &&
		magicalAlmostEqual( p1->d, p2->d, kVectorEpsilon );
}

cBool magicalPlaneIsZero( const cPlane* p )
{
	return
		magicalAlmostZero( p->x, kVectorEpsilon ) &&
		magicalAlmostZero( p->y, kVectorEpsilon ) &&
		magicalAlmostZero( p->z, kVectorEpsilon ) &&
		magicalAlmostZero( p->d, kVectorEpsilon );
}

void magicalPlaneFill( cPlane* out, float x, float y, float z, float d )
{
	out->x = x;
	out->y = y;
	out->z = z;
	out->d = d;
}

void magicalPlaneCopy( cPlane* out, const cPlane* p )
{
	out->x = p->x;
	out->y = p->y;
	out->z = p->z;
	out->d = p->d;
}

/*-----------------------------------------------------------------------------*\
 * 通过法向量与平面到原点距离创建一个平面 done
 *
 * out 结果平面
 * n 表面法向量
 * d 原点到平面的距离
 *-----------------------------------------------------------------------------*/
void magicalPlaneSetNormalAndDistance( cPlane* out, const cVector3* n, float d )
{
	cVector3 nn;
	magicalVector3Normalize( &nn, n );

	out->x = nn.x;
	out->y = nn.y;
	out->z = nn.z;
	out->d = d;
}

/*-----------------------------------------------------------------------------*\
 * 通过平面上任意一点表面法向量创建平面 done
 *
 * 平面方程：dot(p, n) = d
 * 
 * out 结果平面
 * p 平面上任意一点
 * n 表面法向量
 *-----------------------------------------------------------------------------*/
void magicalPlaneSetNormalAndPoint( cPlane* out, const cVector3* n, const cVector3* p )
{
	cVector3 nn;
	magicalVector3Normalize( &nn, n );

	out->x = nn.x;
	out->y = nn.y;
	out->z = nn.z;
	out->d = p->x * nn.x + p->y * nn.y + p->z * nn.z;
}

/*-----------------------------------------------------------------------------*\
 * 通过三个不在一条直线上的点，组成一个由三角形形成的平面 done
 *
 * 左手坐标系：三个点呈顺时针看到的为正面
 *
 * 计算a到b向量与b到c向量的叉乘，可以获得与a到b、b到c互相垂直表面法向量
 * n = cross( b - a, c - b )
 * 
 * out 结果平面
 * a 第一个点
 * b 第二个点
 * c 第三个点
 *-----------------------------------------------------------------------------*/
void magicalPlaneSetPoints( cPlane* out, const cVector3* a, const cVector3* b, const cVector3* c )
{
	cVector3 n, e3, e1;
	
	e3.x = b->x - a->x;
	e3.y = b->y - a->y;
	e3.z = b->z - a->z;

	e1.x = c->x - b->x;
	e1.y = c->y - b->y;
	e1.z = c->z - b->z;

	magicalVector3Cross( &n, &e3, &e1 );
	debugassert( !magicalVector3IsZero( &n ), "invaild operate!" );
	magicalVector3Normalize( &n, &n );

	out->x = n.x;
	out->y = n.y;
	out->z = n.z;
	out->d = a->x * n.x + a->y * n.y + a->z * n.z;
}

void magicalPlaneSetZero( cPlane* out )
{
	out->x = 0.0f;
	out->y = 0.0f;
	out->z = 0.0f;
	out->d = 0.0f;
}

/*-----------------------------------------------------------------------------*\
 * 给平面设置法向量 done
 *
 * out 目标平面
 * n 设置的法向量
 *-----------------------------------------------------------------------------*/
void magicalPlaneSetNormal( cPlane* out, const cVector3* n )
{
	cVector3 nn;
	magicalVector3Normalize( &nn, n );

	out->x = nn.x;
	out->y = nn.y;
	out->z = nn.z;
}

/*-----------------------------------------------------------------------------*\
 * 获取平面的法向量 done
 *
 * out p的法向量
 * p 源平面
 *-----------------------------------------------------------------------------*/
void magicalPlaneGetNormal( cVector3* out, const cPlane* p )
{
	out->x = p->x;
	out->y = p->y;
	out->z = p->z;
}

void magicalPlaneNormalize( cPlane* out, const cPlane* p )
{
	out->x = p->x;
	out->y = p->y;
	out->z = p->z;
	out->d = p->d;

	float n = p->x * p->x + p->y * p->y + p->z * p->z;
	if( magicalAlmostEqual( n, 1.0f, kVectorEpsilon ) )
		return;

	n = sqrtf( n );
	if( magicalAlmostZero( n, kVectorEpsilon ) )
		return;

	n = 1.0f / n;
	out->x *= n;
	out->y *= n;
	out->z *= n;
	out->d *= n;
}

/*-----------------------------------------------------------------------------*\
 * 计算一个点到平面的最近点 done
 *
 * 原点到平面最近点的直线距离最短
 *
 * 最近点公式：
 * q` = q + scale( (d - dot(q, n)), n )
 *
 * out 返回最近点
 * p 目标平面
 * point 任意点
 *-----------------------------------------------------------------------------*/
void magicalPlaneNearestPoint( cVector3* out, const cPlane* p, const cVector3* point )
{
	cVector3 scale_n;
	cVector3 n;

	n.x = p->x;
	n.y = p->y;
	n.z = p->z;

	float distance = p->d - p->x * point->x + p->y * point->y + p->z * point->z;
	
	magicalVector3Scale( &scale_n, &n, distance );
	magicalVector3Add( out, point, &scale_n );
}

/*-----------------------------------------------------------------------------*\
 * 计算平面到3D点的最短距离 done
 *
 * q为目标点，n为平面的法向量，d为原点到平面的距离
 * 计算平面n,d到目标点q的最短距离
 * 公式：d` = dot(q, n) - d
 *
 * out p的法向量
 * p 目标平面
 *-----------------------------------------------------------------------------*/
float magicalPlaneDistanceToPoint( const cPlane* p, const cVector3* point )
{
	return p->x * point->x + p->y * point->y + p->z * point->z - p->d;
}

/*-----------------------------------------------------------------------------*\
 * 分类3D点与面的关系 done
 *
 * p 目标平面
 * point 目标点
 * return 分类结果
 *        +1 在平面前方
 *        -1 在平面后方
 *         0 刚好在平面上
 *-----------------------------------------------------------------------------*/
int magicalPlaneClassifyPoint( const cPlane* p, const cVector3* point )
{
	float distance = p->x * point->x + p->y * point->y + p->z * point->z - p->d;

	if( distance > kVectorEpsilon )
		return kPlaneFront;

	if( distance < -kVectorEpsilon )
		return kPlaneBehind;

	return kPlaneOnPlane;
}

/*-----------------------------------------------------------------------------*\
 * 分类轴对齐包围盒与面的关系 done
 *
 * p 目标平面
 * aabb 包围盒
 * return 分类结果
 *        +1 在平面前方
 *        -1 在平面后方
 *         0 与平面相交
 *-----------------------------------------------------------------------------*/
int magicalPlaneClassifyAABB3( const cPlane* p, const cAABB3* aabb )
{
	float min_d, max_d;

	if( p->x > 0.0f )
	{
		min_d = p->x * aabb->minx;
		max_d = p->x * aabb->maxx;
	}
	else
	{
		min_d = p->x * aabb->maxx;
		max_d = p->x * aabb->minx;
	}

	if( p->y > 0.0f )
	{
		min_d += p->y * aabb->miny;
		max_d += p->y * aabb->maxy;
	}
	else
	{
		min_d += p->y * aabb->maxy;
		max_d += p->y * aabb->miny;
	}

	if( p->z > 0.0f )
	{
		min_d += p->z * aabb->minz;
		max_d += p->z * aabb->maxz;
	}
	else
	{
		min_d += p->z * aabb->maxz;
		max_d += p->z * aabb->minz;
	}

	if( min_d >= p->d ) {
		return kPlaneFront;
	}

	if( max_d <= p->d ) {
		return kPlaneBehind;
	}

	return kPlaneOnPlane;
}

/*-----------------------------------------------------------------------------*\
 * 分配球体与平面的位置关系 done
 *
 * p 平面
 * sp 球体
 * return 分类结果
 *        +1 在平面前方
 *        -1 在平面后方
 *         0 与平面相交
 *-----------------------------------------------------------------------------*/
int magicalPlaneClassifySphere( const cPlane* p, const cSphere* sp )
{
	float distance = p->x * sp->x + p->y * sp->y + p->z * sp->z - p->d;

	if( distance >= sp->r )
		return kPlaneFront;

	if( distance <= -sp->r )
		return kPlaneBehind;

	return kPlaneOnPlane;
}

/*-----------------------------------------------------------------------------*\
 * 判断两个平面是否相交，不相交则为平行 done
 *
 * p1 平面1
 * p2 平面2
 * return 是否相交
 *-----------------------------------------------------------------------------*/
cBool magicalPlaneIntersects( const cPlane* p1, const cPlane* p2 )
{
	cVector3 n1;
	n1.x = p1->x;
	n1.y = p1->y;
	n1.z = p1->z;

	cVector3 n2;
	n2.x = p2->x;
	n2.y = p2->y;
	n2.z = p2->z;

	if( magicalVector3Equals( &n1, &n2 ) )
	{
		return magicalAlmostEqual( p1->d, p2->d, kVectorEpsilon );
	}
	else
	{
		return cTrue;
	}
}

/*-----------------------------------------------------------------------------*\
 * 判断包围盒是否与平面相交 done
 *
 * p 平面
 * aabb 包围盒
 * return 是否相交
 *-----------------------------------------------------------------------------*/
cBool magicalPlaneIntersectsAABB3( const cPlane* p, const cAABB3* aabb )
{
	return magicalPlaneClassifyAABB3( p, aabb ) == 0;
}

/*-----------------------------------------------------------------------------*\
 * 判断球体是否与平面相交 done
 *
 * p 平面
 * sp 球体
 * return 是否相交
 *-----------------------------------------------------------------------------*/
cBool magicalPlaneIntersectsSphere( const cPlane* p, const cSphere* sp )
{
	return magicalPlaneClassifySphere( p, sp ) == 0;
}

cBool magicalPlaneIntersectsRay3( float* outt, const cPlane* p, const cRay3* r3, cBool discard_inside )
{
	return magicalRay3IntersectsPlane( outt, r3, p, discard_inside );
}

/*-----------------------------------------------------------------------------*\
 * 判断平面是否包含3D点 done
 *
 * p 目标平面
 * point 目标点
 * return 是否包含
 *-----------------------------------------------------------------------------*/
cBool magicalPlaneContainsPoint( const cPlane* p, const cVector3* point )
{
	return magicalAlmostZero( p->x * point->x + p->y * point->y + p->z * point->z - p->d, kVectorEpsilon );
}