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
#ifndef __LUA_TABLE_H__
#define __LUA_TABLE_H__

#include "PlatformMacros.h"
#include "Common.h"

#include "LuaMacros.h"
#include "LuaSelector.h"

class LuaState;
class LuaTable;
class LuaFunction;
class LuaTableSelector;

class LuaTable
{
public:
	LuaTable( void );
	LuaTable( std::nullptr_t nt );
	LuaTable( LuaTable&& lt );
	LuaTable( const LuaTable& lt );
	~LuaTable( void );

public:
	LuaTable& operator=( LuaTable&& lt );
	LuaTable& operator=( const LuaTable& lt );
	LuaTable& operator=( std::nullptr_t nt );
	bool operator==( std::nullptr_t nt ) const;
	bool operator!=( std::nullptr_t nt ) const;
	LuaTableSelector& operator[]( const char* key );
	void bind( LuaState* L, LuaTableHandler handler );
	void release( void );

private:
	friend class LuaState;
	LuaTableSelector _selector;
	LuaState* _L = nullptr;
	LuaTableHandler _handler = 0;
	int* _reference_count = nullptr;
};

#endif //__LUA_TABLE_H__