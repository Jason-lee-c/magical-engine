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
#ifndef __MAT4_HPP__
#define __MAT4_HPP__

#include "PlatformMacros.h"
#include "Common.h"

#include "Math3D.h"
#include "Quaternion.h"
#include "Vec3.h"
#include "Vec4.h"

struct Quaternion;
struct Vec3;
struct Vec4;

class MathVec3;
class MathVec4;

// 行优先4X4矩阵
struct Mat4
{
public:
	float mat[16];

public:
	Mat4(
		float m11, float m12, float m13, float m14,
		float m21, float m22, float m23, float m24,
		float m31, float m32, float m33, float m34,
		float m41, float m42, float m43, float m44 );

	inline void fill( 
		float m11, float m12, float m13, float m14,
		float m21, float m22, float m23, float m24,
		float m31, float m32, float m33, float m34,
		float m41, float m42, float m43, float m44 );

	Mat4( const float* m );
	Mat4( const Mat4& m );
	Mat4( void );
	~Mat4( void );

	inline Mat4 operator+( float scalar ) const;
	inline Mat4 operator+( const Mat4& rhs ) const;
	inline Mat4 operator-( float scalar ) const;
	inline Mat4 operator-( const Mat4& rhs ) const;
	inline Mat4 operator*( float scalar ) const;
	inline Mat4 operator*( const Mat4& rhs ) const;
	inline Mat4& operator=( const Mat4& rhs );
	inline Mat4& operator+=( float scalar );
	inline Mat4& operator+=( const Mat4& rhs );
	inline Mat4& operator-=( float scalar );
	inline Mat4& operator-=( const Mat4& rhs );
	inline Mat4& operator*=( float scalar );
	inline Mat4& operator*=( const Mat4& rhs );
	inline bool isIdentity( void ) const;

	inline Mat4 copy( void );
	inline void fill( const float* m );
	inline void fill( const Mat4& m );
	inline void fillIdentity( void );
	inline void fillZero( void );
	inline void fillLookAt( const Vec3& eye, const Vec3& target, const Vec3& up );
	inline void fillPerspective( float fov, float aspect, float znear, float zfar );
	inline void fillOrthographic( float left, float right, float bottom, float top, float near, float far );
	inline void fillScale( const Vec3& scale );
	inline void fillScale( float x, float y, float z );
	inline void fillRotation( const Quaternion& q );
	inline void fillRotation( const Vec3& axis, float angle );
	inline void fillRotationX( float angle );
	inline void fillRotationY( float angle );
	inline void fillRotationZ( float angle );
	inline void fillTranslation( const Vec3& translation );
	inline void fillTranslation( float x, float y, float z );
	
	inline Vec3 getUpVector( void ) const;
	inline Vec3 getDownVector( void ) const;
	inline Vec3 getLeftVector( void ) const;
	inline Vec3 getRightVector( void ) const;
	inline Vec3 getForwardVector( void ) const;
	inline Vec3 getBackVector( void ) const;
	inline void inverse( void );
	inline void negate( void );
	inline void rotate( const Quaternion& q );
	inline void rotate( const Vec3& axis, float angle );
	inline void rotateX( float angle );
	inline void rotateY( float angle );
	inline void rotateZ( float angle );
	inline void scale( float scale );
	inline void scale( float x, float y, float z );
	inline void scale( const Vec3& scale );
	inline void translate( float x, float y, float z );
	inline void translate( const Vec3& t );
    inline void transpose( void );
	inline Vec3 transformVec3( const Vec3& vec ) const;
	inline Vec4 transformVec4( const Vec4& vec ) const;
	inline float determinant( void ) const;
	inline bool decompose( Vec3* translation, Quaternion* rotation, Vec3* scale ) const;
	inline Vec3 getTranslation( void ) const;
	inline Quaternion getRotation( void ) const;
	inline Vec3 getScale( void ) const;

public:
	static const Mat4 IDENTITY;
	static const Mat4 ZERO;
};

class MathMat4
{
public:
	static inline Mat4 fill(
		float m11, float m12, float m13, float m14,
		float m21, float m22, float m23, float m24,
		float m31, float m32, float m33, float m34,
		float m41, float m42, float m43, float m44 );

	static inline Mat4 add( const Mat4& lhs, float scalar );
	static inline Mat4 add( const Mat4& lhs, const Mat4& rhs );
	static inline Mat4 sub( const Mat4& lhs, float scalar );
	static inline Mat4 sub( const Mat4& lhs, const Mat4& rhs );
	static inline Mat4 mul( const Mat4& lhs, float scalar );
	static inline Mat4 mul( const Mat4& lhs, const Mat4& rhs );
	static inline bool isIdentity( const Mat4& m );

	static inline Mat4 copy( const Mat4& m );
	static inline Mat4 fill( const float* m );
	static inline Mat4 fill( const Mat4& m );
	static inline Mat4 fillIdentity( void );
	static inline Mat4 fillZero( void );
	static inline Mat4 fillLookAt( const Vec3& eye, const Vec3& target, const Vec3& up );
	static inline Mat4 fillPerspective( float fov, float aspect, float znear, float zfar );
	static inline Mat4 fillOrthographic( float left, float right, float bottom, float top, float near, float far );
	static inline Mat4 fillScale( const Vec3& scale );
	static inline Mat4 fillScale( float x, float y, float z );
	static inline Mat4 fillRotation( const Quaternion& q );
	static inline Mat4 fillRotation( const Vec3& axis, float angle );
	static inline Mat4 fillRotationX( float angle );
	static inline Mat4 fillRotationY( float angle );
	static inline Mat4 fillRotationZ( float angle );
	static inline Mat4 fillTranslation( const Vec3& translation );
	static inline Mat4 fillTranslation( float x, float y, float z );
	
	static inline Vec3 getUpVector( const Mat4& m );
	static inline Vec3 getDownVector( const Mat4& m );
	static inline Vec3 getLeftVector( const Mat4& m );
	static inline Vec3 getRightVector( const Mat4& m );
	static inline Vec3 getForwardVector( const Mat4& m );
	static inline Vec3 getBackVector( const Mat4& m );
	static inline Mat4 inverse( const Mat4& m );
	static inline Mat4 negate( const Mat4& m );
	static inline Mat4 rotate( const Mat4& m, const Quaternion& q );
	static inline Mat4 rotate( const Mat4& m, const Vec3& axis, float angle );
	static inline Mat4 rotateX( const Mat4& m, float angle );
	static inline Mat4 rotateY( const Mat4& m, float angle );
	static inline Mat4 rotateZ( const Mat4& m, float angle );
	static inline Mat4 scale( const Mat4& m, float scale );
	static inline Mat4 scale( const Mat4& m, float x, float y, float z );
	static inline Mat4 scale( const Mat4& m, const Vec3& scale );
	static inline Mat4 translate( const Mat4& m, float x, float y, float z );
	static inline Mat4 translate( const Mat4& m, const Vec3& t );
    static inline Mat4 transpose( const Mat4& m );
	static inline Vec3 transformVec3( const Mat4& m, const Vec3& vec );
	static inline Vec4 transformVec4( const Mat4& m, const Vec4& vec );
	static inline float determinant( const Mat4& m );
	static inline bool decompose( const Mat4& m, Vec3* translation, Quaternion* rotation, Vec3* scale );
	static inline Vec3 getTranslation( const Mat4& m );
	static inline Quaternion getRotation( const Mat4& m );
	static inline Vec3 getScale( const Mat4& m );
};

#include "Mat4.inl"

#endif //__MAT4_HPP__