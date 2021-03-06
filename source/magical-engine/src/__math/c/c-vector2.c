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
#include "c-vector2.h"

cBool magicalVector2Equals( const cVector2* v1, const cVector2* v2 ) 
{
	return
		magicalAlmostEqual( v1->x, v2->x, kVectorEpsilon )
		&&
		magicalAlmostEqual( v1->y, v2->y, kVectorEpsilon );
}

cBool magicalVector2IsZero( const cVector2* v )
{
	return
		magicalAlmostZero( v->x, kVectorEpsilon )
		&&
		magicalAlmostZero( v->y, kVectorEpsilon );
}

cBool magicalVector2IsOne( const cVector2* v )
{
	return
		magicalAlmostEqual( v->x, 1.0f, kVectorEpsilon )
		&&
		magicalAlmostEqual( v->y, 1.0f, kVectorEpsilon );
}

cBool magicalVector2IsNormalized( const cVector2* v )
{
	return magicalAlmostEqual( v->x * v->x + v->y * v->y, 1.0f, kVectorEpsilon );
}

void magicalVector2Fill( cVector2* out, float x, float y )
{
	out->x = x;
	out->y = y;
}

void magicalVector2Copy( cVector2* out, const cVector2* v )
{
	out->x = v->x;
	out->y = v->y;
}

void magicalVector2SetZero( cVector2* out )
{
	out->x = 0.0f;
	out->y = 0.0f;
}

void magicalVector2SetOne( cVector2* out )
{
	out->x = 1.0f;
	out->y = 1.0f;
}

void magicalVector2FromVector3( cVector2* out, const cVector3* v )
{
	out->x = v->x;
	out->y = v->y;
}

void magicalVector2FromVector4( cVector2* out, const cVector4* v )
{
	out->x = v->x;
	out->y = v->y;
}

void magicalVector2AddScalar( cVector2* out, const cVector2* v, float a )
{
	out->x = v->x + a;
	out->y = v->y + a;
}

void magicalVector2Add( cVector2* out, const cVector2* v1, const cVector2* v2 )
{
	out->x = v1->x + v2->x;
	out->y = v1->y + v2->y;
}

void magicalVector2SubScalar( cVector2* out, const cVector2* v, float a )
{
	out->x = v->x - a;
	out->y = v->y - a;
}

void magicalVector2Sub( cVector2* out, const cVector2* v1, const cVector2* v2 )
{
	out->x = v1->x - v2->x;
	out->y = v1->y - v2->y;
}

void magicalVector2MulScalar( cVector2* out, const cVector2* v, float a )
{
	out->x = v->x * a;
	out->y = v->y * a;
}

void magicalVector2Mul( cVector2* out, const cVector2* v1, const cVector2* v2 )
{
	out->x = v1->x * v2->x;
	out->y = v1->y * v2->y;
}

void magicalVector2DivScalar( cVector2* out, const cVector2* v, float a )
{
	debugassert( !magicalAlmostZero( a, kVectorEpsilon ), "division by 0.f" );

	out->x = v->x / a;
	out->y = v->y / a;
}

void magicalVector2Div( cVector2* out, const cVector2* v1, const cVector2* v2 )
{
	debugassert( !magicalAlmostZero( v2->x, kVectorEpsilon ) && !magicalAlmostZero( v2->y, kVectorEpsilon ), "division by 0.f" );

	out->x = v1->x / v2->x;
	out->y = v1->y / v2->y;
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
float magicalVector2Dot( const cVector2* v1, const cVector2* v2 )
{
	return v1->x * v2->x + v1->y * v2->y;
}

float magicalVector2Cross( const cVector2* v1, const cVector2* v2 )
{
	return v1->x * v2->y - v1->y * v2->x;
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
float magicalVector2DistanceBetween( const cVector2* v1, const cVector2* v2 )
{
	float dx = v2->x - v1->x;
	float dy = v2->y - v1->y;

	return sqrtf( dx * dx + dy * dy );
}

/*-----------------------------------------------------------------------------*\
 * 返回两个点之间距离的平方 done
 *
 * v1 向量1
 * v2 向量2
 * return v1到v2的距离 >= 0 
 *        = 0时 两点在同一位置，或者说两向量大小相同
 *-----------------------------------------------------------------------------*/
float magicalVector2DistanceBetweenSq( const cVector2* v1, const cVector2* v2 )
{
	float dx = v2->x - v1->x;
	float dy = v2->y - v1->y;

	return dx * dx + dy * dy;
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
float magicalVector2Length( const cVector2* v )
{
	return sqrtf( v->x * v->x + v->y * v->y );
}

/*-----------------------------------------------------------------------------*\
 * 返回这个向量长度(大小、模)的平方 done
 *
 * v 求模平方向量
 * return v模平方 >= 0
 *         = 0 零向量
 *         = 1 标准化(单位)向量
 *-----------------------------------------------------------------------------*/
float magicalVector2LengthSq( const cVector2* v )
{
	return v->x * v->x + v->y * v->y;
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
float magicalVector2AngleBetween( const cVector2* v1, const cVector2* v2 )
{
	debugassert( !magicalVector2IsZero( v1 ) && !magicalVector2IsZero( v2 ), "invaild operate!" );

	return magicalSafeAcos( magicalVector2Dot( v1, v2 ) / ( magicalVector2Length( v1 ) * magicalVector2Length( v2 ) ) );
}

/*-----------------------------------------------------------------------------*\
 * 使点参照min与max的位置进行收缩 done
 *
 * out 结果 min <= out <= max
 * v 源向量
 * min 小值
 * max 大值
 *-----------------------------------------------------------------------------*/
void magicalVector2Clamp( cVector2* out, const cVector2* v, const cVector2* min, const cVector2* max )
{
	debugassert( min->x <= max->x && min->y <= max->y, "invaild operate!" );

	out->x = v->x;
	out->y = v->y;

	if( out->x < min->x ) out->x = min->x;
	if( out->x > max->x ) out->x = max->x;
	if( out->y < min->y ) out->y = min->y;
	if( out->y > max->y ) out->y = max->y;
}

/*-----------------------------------------------------------------------------*\
 * 计算向量的倒数形式 done
 *
 * out 结果 v = -v
 * v 源向量
 *-----------------------------------------------------------------------------*/
void magicalVector2Negate( cVector2* out, const cVector2* v )
{
	out->x = -v->x;
	out->y = -v->y;
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
void magicalVector2Normalize( cVector2* out, const cVector2* v )
{
	out->x = v->x;
	out->y = v->y;

	float n = v->x * v->x + v->y * v->y;
	if( magicalAlmostEqual( n, 1.0f, kVectorEpsilon ) )
		return;

	n = sqrtf( n );
	if( magicalAlmostZero( n, kVectorEpsilon ) )
		return;

	n = 1.0f / n;
	out->x *= n;
	out->y *= n;
}

/*-----------------------------------------------------------------------------*\
 * 使2D向量绕原点旋转 done
 * 
 * 2D向量绕原点旋转公式：
 * v`.x = v.x*cos(theta) - v.y*sin(theta)
 * v`.y = v.x*sin(theta) + v.y*cos(theta) 
 *
 * out 旋转后的向量
 * v 源向量
 * angle 旋转的弧度
 *-----------------------------------------------------------------------------*/
void magicalVector2Rotate( cVector2* out, const cVector2* v, float a )
{
	float s = sinf( a );
	float c = cosf( a );

	float rx = v->x * c - v->y * s;
	float ry = v->x * s + v->y * c;

	out->x = rx;
	out->y = ry;
}

/*-----------------------------------------------------------------------------*\
 * 计算向量的缩放 done
 *
 * out 缩放后的向量
 * v 源向量
 * s 缩放系数
 *-----------------------------------------------------------------------------*/
void magicalVector2Scale( cVector2* out, const cVector2* v, float s )
{
	out->x = v->x * s;
	out->y = v->y * s;
}

/*-----------------------------------------------------------------------------*\
 * 返回由两个点组成的线段的中点 done
 *
 * out 返回中点 当两点相等时中点也等于原点
 * v1 向量1
 * v2 向量2
 *-----------------------------------------------------------------------------*/
void magicalVector2MidPointBetween( cVector2* out, const cVector2* v1, const cVector2* v2 )
{
	out->x = ( v1->x + v2->x ) * 0.5f;
	out->y = ( v1->y + v2->y ) * 0.5f;
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
void magicalVector2Project( cVector2* out, const cVector2* p, const cVector2* n )
{
	cVector2 normalize;
	debugassert( !magicalVector2IsZero( n ), "invaild operate!" );
	
	magicalVector2Normalize( &normalize, n );
	float d = magicalVector2Dot( p, &normalize );

	out->x = normalize.x * d;
	out->y = normalize.y * d;

	/*if( magicalVector2Equals( out_h, p ) )
	{
		out_v->x = 0.0f;
		out_v->y = 0.0f;
	}
	else
	{
		out_v->x = p->x - out_h->x;
		out_v->y = p->y - out_h->y;
	}*/
}