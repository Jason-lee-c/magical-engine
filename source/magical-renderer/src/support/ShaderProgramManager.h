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
#ifndef __SHADER_PROGRAM_MANAGER_H__
#define __SHADER_PROGRAM_MANAGER_H__

#include "PlatformMacros.h"
#include "Common.h"
#include "RendererMacros.h"
#include "Mat4.h"
#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"

enum ShaderProgramIndex
{
	kShaderProgramColor = 0,
	kShaderProgramCount, 
};

class ShaderProgramManager
{
public:
	static void init( void );
	static void delc( void );
	static void initPrograms( void );
	static void delcPrograms( void );

	static const Shared<ShaderProgram> getProgram( ShaderProgramIndex index );

public:
	static bool setUniformProgramColor( const Mat4& mvp_matrix, const Color4F& color );
};

#endif //__SHADER_PROGRAM_MANAGER_H__