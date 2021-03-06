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
#ifndef __AABB3_H__
#define __AABB3_H__

NS_MAGICAL_BEGIN

FORWARD_DECLARE

struct AABB3 : public cAABB3
{
public:
	static const AABB3 Zero;
	static AABB3 var;

public:
	AABB3( float minx, float miny, float minz, float maxx, float maxy, float maxz );
	AABB3( const Vector3& min, const Vector3& max );
	AABB3( const AABB3& aabb );
	AABB3( void );

public:
	static inline AABB3 createZero( void );
	static inline AABB3 createFromPoints( const Vector3& min, const Vector3& max );
	static inline AABB3 createFromBox( const Vector3& center, float width, float height, float depth );

public:
#if MAGICAL_MATH_CACHED_POOL_ENABLE
	static void* operator new( size_t s );
	static void operator delete( void* ptr );
#endif
	inline bool equals( const AABB3& aabb ) const;
	inline bool isZero( void ) const;
	inline bool operator==( const AABB3& aabb ) const;
	inline bool operator!=( const AABB3& aabb ) const;
	inline AABB3& operator=( const AABB3& aabb );

public:
	inline void set( const AABB3& aabb );
	inline void setZero( void );
	inline void setScalars( float minx, float miny, float minz, float maxx, float maxy, float maxz );
	inline void fromPoints( const Vector3& min, const Vector3& max );
	inline void fromBox( const Vector3& center, float width, float height, float depth );
	inline void addPoint( float x, float y, float z );
	inline void addPoint( const Vector3& v );
	inline void merge( const AABB3& aabb );
	inline void transform( const Matrix4& m );
	inline AABB3 getMerged( const AABB3& aabb ) const;
	inline float size( void ) const;
	inline float diameterX( void ) const;
	inline float diameterY( void ) const;
	inline float diameterZ( void ) const;
	inline Vector3 centerPoint( void ) const;
	inline Vector3 nearestPoint( const Vector3& point ) const;
	inline void setMinPoint( const Vector3& min );
	inline Vector3 getMinPoint( void ) const;
	inline void setMaxPoint( const Vector3& max );
	inline Vector3 getMaxPoint( void ) const;

	inline bool intersects( const AABB3& aabb ) const;
	inline bool intersectsPart( AABB3& out, const AABB3& aabb ) const;
	inline bool intersectsPlane( const Plane& p ) const;
	inline bool intersectsSphere( const Sphere& sp ) const;
	inline bool intersectsRay3( float& outt, const Ray3& r3, bool discard_inside = false ) const;
	inline bool containsPoint( const Vector3& point ) const;

	//inline bool insideFrustum( const Frustum& frustum ) const;
};

struct MathAABB3
{
public:
	static inline void merge( AABB3& out, const AABB3& aabb1, const AABB3& aabb2 );
	static inline void transform( AABB3& out, const AABB3& aabb, const Matrix4& m );
	static inline void centerPoint( Vector3& out, const AABB3& aabb );
	static inline void nearestPoint( Vector3& out, const AABB3& aabb, const Vector3& point );
};

NS_MAGICAL_END

#endif //__AABB3_H__