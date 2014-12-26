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
#include "../c/cEulerA.h"
#include "../c/cQuaternion.h"
#include "../c/cMatrix4.h"
#include "Vector3.h"
#include "EulerA.h"
#include "Quaternion.h"
#include "Matrix4.h"
#include "EulerA.inl"
#include "MathMacros.h"

const float EulerA::Epsilon = kEpsilonEulerA;
const EulerA EulerA::Identity = EulerA( 0.0f, 0.0f, 0.0f );
EulerA EulerA::var = EulerA::Identity;

EulerA::EulerA( float yaw, float pitch, float roll )
{
	this->yaw = yaw;
	this->pitch = pitch;
	this->roll = roll;
}

EulerA::EulerA( const EulerA& ea )
{
	yaw = ea.yaw;
	pitch = ea.pitch;
	roll = ea.roll;
}

EulerA::EulerA( void )
{
	magicalEulerASetIdentity( this );
}

#if MAGICAL_MATH_CACHED_POOL_ENABLE
#include "CachedPool.h"
static CachedPool<EulerA> s_eulerag_cached_pool( 64, 64 );
#endif

void* EulerA::operator new( size_t s )
{
	if( s != sizeof( EulerA ) )
		return ::operator new( s );

#if MAGICAL_MATH_CACHED_POOL_ENABLE
	return s_eulerag_cached_pool.take();
#else
	return ::operator new( s );
#endif
}

void EulerA::operator delete( void* ptr )
{
	if( ptr == nullptr )
		return;
	
#if MAGICAL_MATH_CACHED_POOL_ENABLE
	s_eulerag_cached_pool.push( ptr );
#else
	return ::operator delete( ptr );
#endif
}