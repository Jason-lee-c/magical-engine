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
#include "cRay3.h"
#include "cMathMacros.h"

cBool magicalRay3Equals( const cRay3 r31, const cRay3 r32 )
{
	return
		magicalAlmostEqual( r31 _o_x, r32 _o_x, kEpsilon ) &&
		magicalAlmostEqual( r31 _o_y, r32 _o_y, kEpsilon ) &&
		magicalAlmostEqual( r31 _o_z, r32 _o_z, kEpsilon ) &&
		magicalAlmostEqual( r31 _d_x, r32 _d_x, kEpsilon ) &&
		magicalAlmostEqual( r31 _d_y, r32 _d_y, kEpsilon ) &&
		magicalAlmostEqual( r31 _d_z, r32 _d_z, kEpsilon );
}

cBool magicalRay3IsZero( const cRay3 r3 )
{
	return
		magicalAlmostZero( r3 _o_x, kEpsilon ) &&
		magicalAlmostZero( r3 _o_y, kEpsilon ) &&
		magicalAlmostZero( r3 _o_z, kEpsilon ) &&
		magicalAlmostZero( r3 _d_x, kEpsilon ) &&
		magicalAlmostZero( r3 _d_y, kEpsilon ) &&
		magicalAlmostZero( r3 _d_z, kEpsilon );
}

void magicalRay3SetScalars( cRay3 out, float ox, float oy, float oz, float dx, float dy, float dz )
{
	out _o_x = ox;
	out _o_y = oy;
	out _o_z = oz;
	out _d_x = dx;
	out _d_y = dy;
	out _d_z = dz;

	magicalRay3DirectionNormalize( out, out );
}

void magicalRay3SetOriginToEnd( cRay3 out, const cVector3 origin, const cVector3 end )
{
	out _o_x = origin _x;
	out _o_y = origin _y;
	out _o_z = origin _z;
	out _d_x = end _x - origin _x;
	out _d_y = end _y - origin _y;
	out _d_z = end _z - origin _z;

	magicalRay3DirectionNormalize( out, out );
}

void magicalRay3SetOriginAndDirection( cRay3 out, const cVector3 origin, const cVector3 direction )
{
	out _o_x = origin _x;
	out _o_y = origin _y;
	out _o_z = origin _z;
	out _d_x = direction _x;
	out _d_y = direction _y;
	out _d_z = direction _z;

	magicalRay3DirectionNormalize( out, out );
}

void magicalRay3SetZero( cRay3 out )
{
	out _o_x = 0.0f;
	out _o_y = 0.0f;
	out _o_z = 0.0f;
	out _d_x = 0.0f;
	out _d_y = 0.0f;
	out _d_z = 0.0f;
}

void magicalRay3Set( cRay3 out, const cRay3 r3 )
{
	out _o_x = r3 _o_x;
	out _o_y = r3 _o_y;
	out _o_z = r3 _o_z;
	out _d_x = r3 _d_x;
	out _d_y = r3 _d_y;
	out _d_z = r3 _d_z;
}

void magicalRay3GetOrigin( cVector3 out, const cRay3 r3 )
{
	out _x = r3 _o_x;
	out _y = r3 _o_y;
	out _z = r3 _o_z;
}

void magicalRay3GetDirection( cVector3 out, const cRay3 r3 )
{
	out _x = r3 _d_x;
	out _y = r3 _d_y;
	out _z = r3 _d_z;
}

void magicalRay3SetOrigin( cRay3 out, const cVector3 origin )
{
	out _o_x = origin _x;
	out _o_y = origin _y;
	out _o_z = origin _z;
}

void magicalRay3SetDirection( cRay3 out, const cVector3 direction )
{
	out _d_x = direction _x;
	out _d_y = direction _y;
	out _d_z = direction _z;

	magicalRay3DirectionNormalize( out, out );
}

/*-----------------------------------------------------------------------------*\
 * 标准化射线的方向部分 done
 *
 * out 结果
 * r3 源射线
 *-----------------------------------------------------------------------------*/
void magicalRay3DirectionNormalize( cRay3 out, const cRay3 r3 )
{
	out _d_x = r3 _d_x;
	out _d_y = r3 _d_y;
	out _d_z = r3 _d_z;

	float n = r3 _d_x * r3 _d_x + r3 _d_y * r3 _d_y + r3 _d_z * r3 _d_z;
	if( magicalAlmostEqual( n, 1.0f, kEpsilonVector3 ) )
		return;

	n = sqrtf( n );
	if( magicalAlmostZero( n, kEpsilonVector3 ) )
		return;

	n = 1.0f / n;
	out _d_x *= n;
	out _d_y *= n;
	out _d_z *= n;
}

/*-----------------------------------------------------------------------------*\
 * 检测射线与3D平面的相交关系，并返回原点到相交点的距离 done
 *
 * dist 距离 相交时有效
 * r3 源射线
 * p 平面
 * discard_inside 是否忽略原点在平面内的相交检测
 * return 是否相交
 *-----------------------------------------------------------------------------*/
void magicalRay3IntersectsPlane3( cRayIntersectResult out, const cRay3 r3, const cPlane3 p, const cBool discard_inside )
{
	int cp;
	float dn;
	cVector3 d;

	cp = magicalPlane3ClassifyPoint( p, r3 );
	if( cp == 0 )
	{
		out _dist = 0.0f;
		out _inst = !discard_inside;
		return;
	}

	d _x = r3 _d_x;
	d _y = r3 _d_y;
	d _z = r3 _d_z;

	dn = magicalVector3Dot( d, p );
	if( magicalAlmostZero( dn, kEpsilonVector3 ) == cFalse )
	{
		if( ( cp == 1 && dn < -kEpsilonVector3 ) || ( cp == -1 && dn > kEpsilonVector3 ) )
		{
			out _dist = ( p _d - magicalVector3Dot( r3, p ) ) / dn; 
			out _inst = cTrue;
			return;
		}
	}

	out _dist = 0.0f;
	out _inst = cFalse;
}

/*-----------------------------------------------------------------------------*\
 * 检测射线与轴对齐包围盒的相交关系，并返回原点到相交点的距离 done
 *
 * dist 距离 相交时有效
 * r3 源射线
 * aabb 包围盒
 * discard_inside 是否忽略原点在包围盒内的相交检测
 * return 是否相交
 *-----------------------------------------------------------------------------*/
void magicalRay3IntersectsAABB3( cRayIntersectResult out, const cRay3 r3, const cAABB3 aabb, const cBool discard_inside )
{
	float t;
	cVector3 p;

	if( r3 _o_x >= aabb _min_x &&
		r3 _o_y >= aabb _min_y &&
		r3 _o_z >= aabb _min_z &&
		r3 _o_x <= aabb _max_x &&
		r3 _o_y <= aabb _max_y &&
		r3 _o_z <= aabb _max_z )
	{
		out _dist = 0.0f;
		out _inst = !discard_inside;
		return;
	}

	if( magicalAlmostZero( r3 _d_x, kEpsilonVector3 ) == cFalse )
	{
		if( r3 _d_x > 0.0f )
		{
			t = ( aabb _min_x - r3 _o_x ) / r3 _d_x;
		}
		else
		{
			t = ( aabb _max_x - r3 _o_x ) / r3 _d_x;
		}

		if( t > 0.0f )
		{
			p _x = r3 _o_x + r3 _d_x * t;
			p _y = r3 _o_y + r3 _d_y * t;
			p _z = r3 _o_z + r3 _d_z * t;

			if( p _y >= aabb _min_y &&
				p _y <= aabb _max_y &&
				p _z >= aabb _min_z &&
				p _z <= aabb _max_z )
			{
				out _dist = t;
				out _inst = cTrue;
				return;
			}
		}
	}

	if( magicalAlmostZero( r3 _d_y, kEpsilonVector3 ) == cFalse )
	{
		if( r3 _d_y > 0.0f )
		{
			t = ( aabb _min_y - r3 _o_y ) / r3 _d_y;
		}
		else
		{
			t = ( aabb _max_y - r3 _o_y ) / r3 _d_y;
		}

		if( t > 0.0f )
		{
			p _x = r3 _o_x + r3 _d_x * t;
			p _y = r3 _o_y + r3 _d_y * t;
			p _z = r3 _o_z + r3 _d_z * t;

			if( p _z >= aabb _min_z &&
				p _z <= aabb _max_z &&
				p _x >= aabb _min_x &&
				p _x <= aabb _max_x )
			{
				out _dist = t;
				out _inst = cTrue;
				return;
			}
		}
	}

	if( magicalAlmostZero( r3 _d_z, kEpsilonVector3 ) == cFalse )
	{
		if( r3 _d_z > 0.0f )
		{
			t = ( aabb _min_z - r3 _o_z ) / r3 _d_z;
		}
		else
		{
			t = ( aabb _max_z - r3 _o_z ) / r3 _d_z;
		}

		if( t > 0.0f )
		{
			p _x = r3 _o_x + r3 _d_x * t;
			p _y = r3 _o_y + r3 _d_y * t;
			p _z = r3 _o_z + r3 _d_z * t;

			if( p _x >= aabb _min_x &&
				p _x <= aabb _max_x &&
				p _y >= aabb _min_y &&
				p _y <= aabb _max_y )
			{
				out _dist = t;
				out _inst = cTrue;
				return;
			}
				
		}
	}
	
	out _dist = 0.0f;
	out _inst = cFalse;
}

/*-----------------------------------------------------------------------------*\
 * 检测射线与球体的相交情况，并返回起点到交点的长度 done
 *
 * dist 返回射线到球体相交点的距离 当相交时有效
 *      有可能在原点就已经相交
 * r3 源射线
 * sp 球体
 * discard_inside 是否忽略原点在球体内的相交检测
 * return 是否相交
 *-----------------------------------------------------------------------------*/
void magicalRay3IntersectsSphere3( cRayIntersectResult out, const cRay3 r3, const cSphere3 sp, const cBool discard_inside )
{
	cVector3 ve, vd;
	float a, esq, f, fsq;

	magicalRay3GetDirection( vd, r3 );
	magicalVector3Sub( ve, sp, r3 );

	esq = magicalVector3LengthSq( ve );
	if( esq <= sp _r * sp _r )
	{
		out _dist = 0.0f;
		out _inst = !discard_inside;
		return;
	}

	a = magicalVector3Dot( ve, vd );
	fsq = sp _r * sp _r - esq + a * a;

	if( fsq < 0.0f )
	{
		out _dist = 0.0f;
		out _inst = cFalse;
		return;
	}

	f = sqrtf( fsq );
	out _dist = a - f;
	out _inst = cTrue;
}