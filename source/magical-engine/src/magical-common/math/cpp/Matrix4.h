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
#ifndef __MATRIX4_H__
#define __MATRIX4_H__

struct Vector3;
struct Vector4;
struct AxisA;
struct EulerA;
struct Quaternion;

struct Matrix4 : public cMatrix4
{
public:
	static const Matrix4 Identity;
	static const Matrix4 Zero;
	static Matrix4 var;

public:
	Matrix4( const float* m );
	Matrix4( float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24, float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44 );
	Matrix4( const Matrix4& m );
	Matrix4( void );

public:
	static inline Matrix4 createIdentity( void );
	static inline Matrix4 createZero( void );
	static inline void mulScalar( Matrix4& out, const Matrix4& m, float a );
	static inline void mul( Matrix4& out, const Matrix4& m1, const Matrix4& m2 );
	static inline void getUpVector( Vector3& out, const Matrix4& m );
	static inline void getDownVector( Vector3& out, const Matrix4& m );
	static inline void getLeftVector( Vector3& out, const Matrix4& m );
	static inline void getRightVector( Vector3& out, const Matrix4& m );
	static inline void getForwardVector( Vector3& out, const Matrix4& m );
	static inline void getBackVector( Vector3& out, const Matrix4& m );
	static inline void getTranslation( Vector3& out, const Matrix4& m );
	static inline void getScale( Vector3& out, const Matrix4& m );
	static inline void getRotationQuaternion( Quaternion& out, const Matrix4& m );
	static inline bool inverse( Matrix4& out, const Matrix4& m );
	static inline void transpose( Matrix4& out, const Matrix4& m );
	static inline void negate( Matrix4& out, const Matrix4& m );

public:
	static void* operator new( size_t s );
	static void operator delete( void* ptr );
	inline bool equals( const Matrix4& m ) const;
	inline bool isZero( void ) const;
	inline bool isIdentity( void ) const;
	inline bool operator==( const Matrix4& m ) const;
	inline bool operator!=( const Matrix4& m ) const;
	inline float operator[]( const unsigned int i ) const;
	inline Matrix4 operator*( float a ) const;
	inline Matrix4 operator*( const Matrix4& m ) const;
	inline Matrix4& operator*=( float a );
	inline Matrix4& operator*=( const Matrix4& m );
	inline Matrix4& operator=( const Matrix4& m );

public:
	inline void set( const float* m );
	inline void set( const Matrix4& m );
	inline void setIdentity( void );
	inline void setZero( void );
	inline void setLookAt( const Vector3& eye, const Vector3& target, const Vector3& up );
	inline void setPerspective( float fov, float aspect, float znear, float zfar );
	inline void setOrth( float left, float right, float bottom, float top, float near, float far );
	inline void setupTranslation( float x, float y, float z );
	inline void setupTranslation( const Vector3& t );
	inline void setupScale( float x, float y, float z );
	inline void setupScale( const Vector3& s );
	inline void setupRotationX( float angle );
	inline void setupRotationY( float angle );
	inline void setupRotationZ( float angle );
	inline void setupRotationAxisA( const Vector3& axis, float angle );
	inline void setupRotationAxisA( const AxisA& aa );
	inline void setupRotationEulerA( float yaw, float pitch, float roll );
	inline void setupRotationEulerA( const EulerA& ea );
	inline void setupRotationQuaternion( const Quaternion& q );

public:
	inline Vector3 getUpVector( void ) const;
	inline Vector3 getDownVector( void ) const;
	inline Vector3 getLeftVector( void ) const;
	inline Vector3 getRightVector( void ) const;
	inline Vector3 getForwardVector( void ) const;
	inline Vector3 getBackVector( void ) const;
	inline void setTranslation( float x, float y, float z );
	inline void setTranslation( const Vector3& t );
	inline Vector3 getTranslation( void ) const;
	inline Vector3 getScale( void ) const;
	inline Quaternion getRotationQuaternion( void ) const;
	inline bool inverse( void );
	inline void transpose( void );
	inline void negate( void );
	inline bool getInversed( Matrix4& out ) const;
	inline Matrix4 getTransposed( void ) const;
	inline Matrix4 getNegated( void ) const;
	inline float determinant( void ) const;
};

#endif //__MATRIX4_H__