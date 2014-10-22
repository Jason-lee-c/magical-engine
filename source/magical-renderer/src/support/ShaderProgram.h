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
#ifndef __SHADER_PROGRAM_H__
#define __SHADER_PROGRAM_H__

#include "PlatformMacros.h"
#include "Common.h"
#include "Reference.h"

class ShaderProgram : public Reference
{
public:
	ShaderProgram( void );
	virtual ~ShaderProgram( void );
	static Shared<ShaderProgram> create( void );

public:
	void setVertexSource( const char* vertex_src );
	void setFragmentSource( const char* fragment_src );
	bool build( void );
	bool link( void );
	void cleanup( void );
	inline uint32_t getId( void ) const { return _program_id; }
	bool isReady( void ) const;

private:
	std::string _vertex_src;
	std::string _fragment_src;
	uint32_t _program_id;
	bool _has_built;
	bool _has_linked;
};

#endif //__SHADER_PROGRAM_H__