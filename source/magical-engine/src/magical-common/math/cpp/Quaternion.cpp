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
#include "../c/cVector3.h"
#include "../c/cMatrix4.h"
#include "../c/cAxisAngle.h"
#include "../c/cEulerAngles.h"
#include "../c/cQuaternion.h"
#include "Vector3.h"
#include "Matrix4.h"
#include "AxisAngle.h"
#include "EulerAngles.h"
#include "Quaternion.h"
#include "Quaternion.inl"
#include "MathMacros.h"

const Quaternion Quaternion::Identity = Quaternion( 0.0f, 0.0f, 0.0f, 1.0f );
const Quaternion Quaternion::Zero = Quaternion( 0.0f, 0.0f, 0.0f, 0.0f );

Quaternion Quaternion::placeholder = Quaternion::Identity;
Quaternion Quaternion::temp = Quaternion::Identity;

Quaternion::Quaternion( const float x, const float y, const float z, const float w )
: x( x )
, y( y )
, z( z )
, w( w )
{

}

Quaternion::Quaternion( const Matrix4& m )
{
	magicalQuaternionFromMatrix4( tofpointer( this ), tofpointer( &m ) );
}

Quaternion::Quaternion( const AxisAngle& aa )
{
	magicalQuaternionFromAxisAngle( tofpointer( this ), tofpointer( &aa ) );
}

Quaternion::Quaternion( const EulerAngles& ea )
{
	magicalQuaternionFromEulerAngles( tofpointer( this ), tofpointer( &ea ) );
}

Quaternion::Quaternion( const Quaternion& q )
: x( q.x )
, y( q.y )
, z( q.z )
, w( q.w )
{

}

Quaternion::Quaternion( void )
: x( 0.0f )
, y( 0.0f )
, z( 0.0f )
, w( 1.0f )
{

}

#if MAGICAL_MATH_CACHED_POOL_ENABLE
#include "CachedPool.h"
static CachedPool<Quaternion> s_quaternion_cached_pool( 32, 32 );
#endif

void* Quaternion::operator new( size_t s )
{
	if( s != sizeof( Quaternion ) )
		return ::operator new( s );

#if MAGICAL_MATH_CACHED_POOL_ENABLE
	return s_quaternion_cached_pool.take();
#else
	return ::operator new( s );
#endif
}

void Quaternion::operator delete( void* ptr )
{
	if( ptr == nullptr )
		return;
	
#if MAGICAL_MATH_CACHED_POOL_ENABLE
	s_quaternion_cached_pool.push( ptr );
#else
	return ::operator delete( ptr );
#endif
}