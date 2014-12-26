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
#include "cVector3.h"
#include "cMathMacros.h"

cBool magicalVector3Equals( const cVector3* v1, const cVector3* v2 )
{
	return
		magicalAlmostEqual( v1->x, v2->x, kEpsilonVector3 ) &&
		magicalAlmostEqual( v1->y, v2->y, kEpsilonVector3 ) &&
		magicalAlmostEqual( v1->z, v2->z, kEpsilonVector3 );
}

cBool magicalVector3IsZero( const cVector3* v )
{
	return
		magicalAlmostZero( v->x, kEpsilonVector3 ) &&
		magicalAlmostZero( v->y, kEpsilonVector3 ) &&
		magicalAlmostZero( v->z, kEpsilonVector3 );
}

cBool magicalVector3IsOne( const cVector3* v )
{
	return
		magicalAlmostEqual( v->x, 1.0f, kEpsilonVector3 ) &&
		magicalAlmostEqual( v->y, 1.0f, kEpsilonVector3 ) &&
		magicalAlmostEqual( v->z, 1.0f, kEpsilonVector3 );
}

cBool magicalVector3IsNormalized( const cVector3* v )
{
	return magicalAlmostEqual( v->x * v->x + v->y * v->y + v->z * v->z, 1.0f, kEpsilonVector3 );
}

void magicalVector3Fill( cVector3* out, float x, float y, float z )
{
	out->x = x;
	out->y = y;
	out->z = z;
}

void magicalVector3Copy( cVector3* out, const cVector3* v )
{
	out->x = v->x;
	out->y = v->y;
	out->z = v->z;
}

void magicalVector3SetZero( cVector3* out )
{
	out->x = 0.0f;
	out->y = 0.0f;
	out->z = 0.0f;
}

void magicalVector3SetOne( cVector3* out )
{
	out->x = 1.0f;
	out->y = 1.0f;
	out->z = 1.0f;
}

void magicalVector3FromVector2( cVector3* out, const cVector2* v )
{
	out->x = v->x;
	out->y = v->y;
	out->z = 0.0f;
}

void magicalVector3FromVector4( cVector3* out, const cVector4* v )
{
	out->x = v->x;
	out->y = v->y;
	out->z = v->z;
}

void magicalVector3AddScalar( cVector3* out, const cVector3* v, float a )
{
	out->x = v->x + a;
	out->y = v->y + a;
	out->z = v->z + a;
}

void magicalVector3Add( cVector3* out, const cVector3* v1, const cVector3* v2 )
{
	out->x = v1->x + v2->x;
	out->y = v1->y + v2->y;
	out->z = v1->z + v2->z;
}

void magicalVector3SubScalar( cVector3* out, const cVector3* v, float a )
{
	out->x = v->x - a;
	out->y = v->y - a;
	out->z = v->z - a;
}

void magicalVector3Sub( cVector3* out, const cVector3* v1, const cVector3* v2 )
{
	out->x = v1->x - v2->x;
	out->y = v1->y - v2->y;
	out->z = v1->z - v2->z;
}

void magicalVector3MulScalar( cVector3* out, const cVector3* v, float a )
{
	out->x = v->x * a;
	out->y = v->y * a;
	out->z = v->z * a;
}

void magicalVector3Mul( cVector3* out, const cVector3* v1, const cVector3* v2 )
{
	out->x = v1->x * v2->x;
	out->y = v1->y * v2->y;
	out->z = v1->z * v2->z;
}

void magicalVector3DivScalar( cVector3* out, const cVector3* v, float a )
{
	debugassert( !magicalAlmostZero( a, kEpsilonVector3 ), "division by 0.f" );

	out->x = v->x / a;
	out->y = v->y / a;
	out->z = v->z / a;
}

void magicalVector3Div( cVector3* out, const cVector3* v1, const cVector3* v2 )
{
	debugassert( !magicalVector3IsZero( v2 ), "division by 0.f" );

	out->x = v1->x / v2->x;
	out->y = v1->y / v2->y;
	out->z = v1->z / v2->z;
}

/*-----------------------------------------------------------------------------*\
 * 返回两个向量的点乘运算 done
 * 
 * 点乘公式：dot(a,b) = a.x*b.x + a.y*b.y
 *
 * 点乘结果等于向量长度与向量夹角的cos值的积
 * 点乘夹角公式：dot(a,b) = length(a) * length(b) * cos(theta)
 *
 * 在3D中两向量的夹角是在包含两向量的平面中定义的
 *
 * v1 向量1
 * v2 向量2
 * return 点乘结果
 *        > 0 两向量接近同一方向
 *        = 0 两向量垂直
 *        < 0 两向量接近相反方向
 *-----------------------------------------------------------------------------*/
float magicalVector3Dot( const cVector3* v1, const cVector3* v2 )
{
	return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}

/*-----------------------------------------------------------------------------*\
 * 返回两个点之间的距离(a向量到b向量的距离) done
 * 
 * 距离公式：distance(a,b) = length(d);
 * 其中向量d = b-a
 *
 * v1 向量1
 * v2 向量2
 * return 距离>= 0 当距离=0时 两点在同一位置，或者说两向量大小相同
 *-----------------------------------------------------------------------------*/
float magicalVector3DistanceBetween( const cVector3* v1, const cVector3* v2 )
{
	float dx = v2->x - v1->x;
	float dy = v2->y - v1->y;
	float dz = v2->z - v1->z;

	return sqrtf( dx * dx + dy * dy + dz * dz );
}

/*-----------------------------------------------------------------------------*\
 * 返回两个点之间距离的平方 done
 *
 * v1 向量1
 * v2 向量2
 * return v1到v2的距离 >= 0 
 *        = 0时 两点在同一位置，或者说两向量大小相同
 *-----------------------------------------------------------------------------*/
float magicalVector3DistanceBetweenSq( const cVector3* v1, const cVector3* v2 )
{
	float dx = v2->x - v1->x;
	float dy = v2->y - v1->y;
	float dz = v2->z - v1->z;

	return dx * dx + dy * dy + dz * dz;
}

/*-----------------------------------------------------------------------------*\
 * 返回这个向量的长度(大小、模) done
 *
 * 求模公式 length = sqrt(a^2 + b^2 + ... n^2)
 *
 * v 求模向量
 * return v的模 >= 0
 *        = 0 零向量
 *        = 1 标准化(单位)向量
 *-----------------------------------------------------------------------------*/
float magicalVector3Length( const cVector3* v )
{
	return sqrtf( v->x * v->x + v->y * v->y + v->z * v->z );
}

/*-----------------------------------------------------------------------------*\
 * 返回这个向量长度(大小、模)的平方 done
 *
 * v 求模平方向量
 * return v模平方 >= 0
 *         = 0 零向量
 *         = 1 标准化(单位)向量
 *-----------------------------------------------------------------------------*/
float magicalVector3LengthSq( const cVector3* v )
{
	return v->x * v->x + v->y * v->y + v->z * v->z;
}

/*-----------------------------------------------------------------------------*\
 * 返回两个向量之间的夹角(弧度单位) done
 * 
 * 参考点乘夹角公式
 * 转换：theta = acos( dot(a,b) / length(a) * length(b) )
 *
 * 两个参与运算的向量都不能为零向量
 *
 * v1 向量1
 * v2 向量2
 * return 夹角弧度 >=0 and <= PI
 *        = 0 两向量方向一致
 *-----------------------------------------------------------------------------*/
float magicalVector3AngleBetween( const cVector3* v1, const cVector3* v2 )
{
	debugassert( !magicalVector3IsZero( v1 ) && !magicalVector3IsZero( v2 ), "invaild operate!" );

	return magicalSafeAcos( magicalVector3Dot( v1, v2 ) / ( magicalVector3Length( v1 ) * magicalVector3Length( v2 ) ) );
}

/*-----------------------------------------------------------------------------*\
 * 计算向量v1与向量v2的叉乘结果 done
 *
 * 叉乘得到的向量垂直于原来的两个向量
 * 叉乘的结果也等于以向量v1和向量v2为两边的平行四边形面积
 *
 * 叉乘公式：
 * [x1]   [x2]   [y1z2 - z1y2]
 * [y1] X [y2] = [z1x2 - x1z2]
 * [z1]   [z2]   [x1y2 - y1x2]
 *
 * 叉乘结果向量的长度等于向量的大小与向量夹角sin值的积
 * 叉乘夹角公式：length(cross(a,b)) = length(a) * length(b) * sin(theta)
 *
 * 叉乘的结果(非零)与向量v1或v2进行点乘运算，其结果为0(垂直)
 *
 * 在左手坐标系中，如果向量v1头部连接向量v2尾部呈顺时针，则叉乘结果指向观察者
 *
 * out 叉乘结果向量 
 *     = 0 如果向量v1与向量v2平行或任意一个为零向量，则结果为零向量
 * v1  向量1
 * v2  向量2
 *-----------------------------------------------------------------------------*/
void magicalVector3Cross( cVector3* out, const cVector3* v1, const cVector3* v2 )
{
	float rx = v1->y * v2->z - v1->z * v2->y;
	float ry = v1->z * v2->x - v1->x * v2->z;
	float rz = v1->x * v2->y - v1->y * v2->x;

	out->x = rx;
	out->y = ry;
	out->z = rz;
}

/*-----------------------------------------------------------------------------*\
 * 使点参照min与max的位置进行收缩 done
 *
 * out 结果 min <= out <= max
 * v 源向量
 * min 小值
 * max 大值
 *-----------------------------------------------------------------------------*/
void magicalVector3Clamp( cVector3* out, const cVector3* v, const cVector3* min, const cVector3* max )
{
	debugassert( min->x <= max->x && min->y <= max->y && min->z <= max->z, "invaild operate!" );

	out->x = v->x;
	out->y = v->y;
	out->z = v->z;

	if( out->x < min->x ) out->x = min->x;
	if( out->x > max->x ) out->x = max->x;
	if( out->y < min->y ) out->y = min->y;
	if( out->y > max->y ) out->y = max->y;
	if( out->z < min->z ) out->z = min->z;
	if( out->z > max->z ) out->z = max->z;
}

/*-----------------------------------------------------------------------------*\
 * 计算向量的倒数形式 done
 *
 * out 结果 v = -v
 * v 源向量
 *-----------------------------------------------------------------------------*/
void magicalVector3Negate( cVector3* out, const cVector3* v )
{
	out->x = -v->x;
	out->y = -v->y;
	out->z = -v->z;
}

/*-----------------------------------------------------------------------------*\
 * 计算向量的标准化 done
 * 
 * 向量标准化公式：normalize(a) = a / length(a)
 *
 * 当向量已经标准化或模接近0，则标准化失败
 *
 * out 结果 out = normalize(v)
 * v 源向量
 *-----------------------------------------------------------------------------*/
void magicalVector3Normalize( cVector3* out, const cVector3* v )
{
	out->x = v->x;
	out->y = v->y;
	out->z = v->z;

	float n = v->x * v->x + v->y * v->y + v->z * v->z;
	if( magicalAlmostEqual( n, 1.0f, kEpsilonVector3 ) )
		return;

	n = sqrtf( n );
	if( magicalAlmostZero( n, kEpsilonVector3 ) )
		return;

	n = 1.0f / n;
	out->x *= n;
	out->y *= n;
	out->z *= n;
}

/*-----------------------------------------------------------------------------*\
 * 计算向量的缩放 done
 *
 * out 缩放后的向量
 * v 源向量
 * s 缩放系数
 *-----------------------------------------------------------------------------*/
void magicalVector3Scale( cVector3* out, const cVector3* v, float s )
{
	out->x = v->x * s;
	out->y = v->y * s;
	out->z = v->z * s;
}

/*-----------------------------------------------------------------------------*\
 * 返回由两个点组成的线段的中点 done
 *
 * out 返回中点 当两点相等时中点也等于原点
 * v1 向量1
 * v2 向量2
 *-----------------------------------------------------------------------------*/
void magicalVector3MidPointBetween( cVector3* out, const cVector3* v1, const cVector3* v2 )
{
	out->x = ( v1->x + v2->x ) * 0.5f;
	out->y = ( v1->y + v2->y ) * 0.5f;
	out->z = ( v1->z + v2->z ) * 0.5f;
}

/*-----------------------------------------------------------------------------*\
 * 计算向量p到向量n的投影，结果由向量out(平行于n)返回 done
 * 
 * 投影结果满足 p = h + v
 *
 * 平行投影向量公式：h = n * ( dot(p,n) / lengthSq(n) )
 * 如果n为单位向量 ：h = n * ( dot(p,n) )
 * 垂直投影向量公式：v = p - h;
 *
 * 向量p或向量n为零向量时投影无意义
 *
 * 如果向量p与向量n方向一致，则 h = p, v = 0
 * 
 * out 平行与n的投影分量
 * p 源向量
 * n 投影目标向量
 *-----------------------------------------------------------------------------*/
void magicalVector3Project( cVector3* out, const cVector3* p, const cVector3* n )
{
	float d;
	cVector3 normalize;

	debugassert( !magicalVector3IsZero( n ), "invaild operate!" );
	
	magicalVector3Normalize( &normalize, n );
	d = magicalVector3Dot( p, &normalize );

	out->x = normalize.x * d;
	out->y = normalize.y * d;
	out->z = normalize.z * d;
}