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
#ifndef __RENDER_COMMAND_H__
#define __RENDER_COMMAND_H__

#include "magical-macros.h"
#include "magical-math.h"
#include "Common.h"
#include "Reference.h"

#include "RenderDefine.h"
#include "VertexBufferObject.h"
#include "ShaderProgram.h"
#include "Shaders.h"
#include <functional>

NAMESPACE_MAGICAL

class RenderCommand : public Reference
{
public:
	RenderCommand( void );
	virtual ~RenderCommand( void );

public:
	int getFeature( void ) const { return m_feature; }
	ShaderProgram* getProgram( void ) const { return m_program; }
	void setProgram( ShaderProgram* program );
	void setPreDrawProcess( const std::function<void (ShaderProgram*)> process );

public:
	void callPreDrawProcess( void );

protected:
	int m_feature = 0;
	ShaderProgram* m_program = nullptr;
	std::function<void (ShaderProgram*)> m_pre_draw_process = nullptr;
};

class BatchCommand : public RenderCommand
{
public:
	enum : int { Feature = 1001 };

public:
	BatchCommand( void );
	virtual ~BatchCommand( void );

public:
	Shapes getShape( void ) const { return m_shape; }
	VertexBufferObject* getVertexBufferObject( void ) const { return m_vbo; }
	void setShape( const Shapes shape );
	void setVertexBufferObject( VertexBufferObject* vbo );

protected:
	Shapes m_shape = Shapes::Triangles;
	VertexBufferObject* m_vbo = nullptr;
};

NAMESPACE_END

#endif //__RENDER_COMMAND_H__
