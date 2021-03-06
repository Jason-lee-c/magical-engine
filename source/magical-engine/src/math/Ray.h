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
#ifndef __RAY3_H__
#define __RAY3_H__

#include "magical-macros.h"

NAMESPACE_MAGICAL

struct Ray
{
	union
	{
		struct {
			float ox;
			float oy;
			float oz;
			float dx;
			float dy;
			float dz;
		};
		struct {
			Vector3 origin;
			Vector3 direction;
		};
	};

public:
	static const Ray Invalid;

public:
	inline Ray( const Vector3& origin, const Vector3& direction );
	inline Ray( const Ray& ray );
	inline Ray( void );

public:
	inline bool operator==( const Ray& ray ) const;
	inline bool operator!=( const Ray& ray ) const;
	inline Ray& operator=( const Ray& ray );

public:
	inline bool equals( const Ray& ray ) const;
	inline bool isValid( void ) const;
	inline void set( const Vector3& origin, const Vector3& direction );
	inline void set( const Ray& ray );
	inline void setOriginToEnd( const Vector3& origin, const Vector3& end );
	static inline Ray createOriginToEnd( const Vector3& origin, const Vector3& end );

public:
	bool intersects( float& distance, const Plane& plane, bool discard_inside = false ) const;
	bool intersects( float& distance, const Box& box, bool discard_inside = false ) const;
	bool intersects( float& distance, const Sphere& sphere, bool discard_insid = false ) const;
};

NAMESPACE_END

#endif //__RAY3_H__