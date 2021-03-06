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
#include "Common.h"
#include "Utils.h"

#ifdef MAGICAL_DEBUG
#include <mutex>
#endif

#ifdef MAGICAL_WIN32
#include <windows.h>
#endif

static bool _last_error = false;
static char _last_error_info[ MAGICAL_ERROR_MAX_LENGTH ];
//static int64_t s_time_marker = 0;

//#ifdef MAGICAL_DEBUG
//static struct {
//	int construct_count;
//	int destruct_count;
//} 
//s_engine_objects_listener, 
//s_custom_objects_listener;
//
//static std::mutex s_olc_mutex;
//static std::mutex s_old_mutex;
//static bool s_is_engine_objects_listener_started = false;
//static bool s_is_custom_objects_listener_started = false;
//#endif

//#include <algorithm>

MAGICALAPI bool MAGICAL_IS_ERROR( void )
{
	return _last_error;
}

MAGICALAPI void MAGICAL_IGNORE_LAST_ERROR( void )
{
	_last_error = false;
}

MAGICALAPI void MAGICAL_SET_LAST_ERROR_IMPL( const char* info, const char* file, int line )
{
	if( info == nullptr )
		return;

	if( file )
		sprintf( _last_error_info, "%s %s:%d", info, file, line );
	else
		strcpy( _last_error_info, info );

	_last_error = true;
}

MAGICALAPI const char* MAGICAL_GET_LAST_ERROR_INFO( void )
{
	if( strlen( _last_error_info ) > 0 )
	{
		return _last_error_info;
	}
	else
	{
		return "none";
	}
}

MAGICALAPI void MAGICAL_SHOW_LAST_ERROR( void )
{
	if( !MAGICAL_IS_ERROR() ) return;

#ifdef MAGICAL_WIN32
	std::stringstream stext;
	stext << MAGICAL_GET_LAST_ERROR_INFO() << "\n\n";
	stext << "请查看程序日志清单，追溯错误来源！";

	std::wstring wtext = magical::System::utf8ToUnicode( stext.str() );
	MessageBoxW( nullptr, wtext.c_str(), L"运行时错误! 魔幻引擎 \t", MB_ICONERROR | MB_OK );
#endif
}

MAGICALAPI void MAGICAL_LOG_LAST_ERROR( bool newline )
{
	USING_NS_MAGICAL;

	char temp[ MAGICAL_ERROR_MAX_LENGTH + 12 ];
	const char* last_error = MAGICAL_GET_LAST_ERROR_INFO();
	sprintf( temp, "[ERROR]: %s", last_error );

	if( newline )
	{
		Log::writeLine( Log::Error, temp );
	}
	else
	{
		Log::write( Log::Error, temp );
	}
}

NAMESPACE_MAGICAL
#ifdef MAGICAL_WIN32
#ifdef MessageBox
#undef MessageBox
#endif
#endif
void MessageBox::show( const char* msg, const char* title )
{
#ifdef MAGICAL_WIN32
	MessageBoxA( nullptr, msg, title, MB_OK );
#endif
}
NAMESPACE_END

MAGICALAPI void MAGICAL_ASSERT_IMPL( const char* exp, const char* msg, const char* file, int line )
{
#ifdef MAGICAL_WIN32
	std::stringstream stext;
	stext << file << "\n\nLine: " << line << "\n\n";
	stext << "条件表达式：" << "(" << exp << ") " << msg << "\n\n";
	stext << "是否跟进断点，查看调用堆栈？";

	std::wstring wtext = magical::System::utf8ToUnicode( stext.str() );
	if( MessageBoxW( nullptr, wtext.c_str(), L"Assertion failed! 魔幻引擎 \t", MB_ICONERROR | MB_YESNO ) == IDYES )
	{
		_CrtDbgBreak();
	}
	else
	{
		exit( -1 );
	}
#endif
}

//bool magicalIsTimerStarted( void )
//{
//	return s_timer_mark_var != 0;
//}
//
//void magicalStartTimer( void )
//{
//	USING_NS_MAGICAL;
//
//	s_timer_mark_var = TimeUtils::currentMicroseconds();
//}
//
//double magicalEndTimer( void )
//{
//	USING_NS_MAGICAL;
//
//	if( s_timer_mark_var == 0 )
//		return 0.0;
//
//	double result;
//	int64_t now = TimeUtils::currentMicroseconds();
//	result = cmax( 0.0, ( now - s_timer_mark_var ) / 1000000.0 );
//	s_timer_mark_var = 0;
//	return result;
//}

//#ifdef MAGICAL_DEBUG
//void magicalStartObjectsListener( int listener )
//{
//	if( listener == kEngineObjectsListener )
//	{
//		s_engine_objects_listener.destruct_count = 0;
//		s_engine_objects_listener.construct_count = 0;
//		s_is_engine_objects_listener_started = true;
//	}
//	else
//	{
//		s_custom_objects_listener.destruct_count = 0;
//		s_custom_objects_listener.construct_count = 0;
//		s_is_custom_objects_listener_started = true;
//	}
//}
//
//void magicalEndObjectsListener( int listener )
//{
//	if( listener == kEngineObjectsListener )
//	{
//		s_engine_objects_listener.destruct_count = 0;
//		s_engine_objects_listener.construct_count = 0;
//		s_is_engine_objects_listener_started = false;
//	}
//	else
//	{
//		s_custom_objects_listener.destruct_count = 0;
//		s_custom_objects_listener.construct_count = 0;
//		s_is_custom_objects_listener_started = false;
//	}
//}
//
//bool magicalIsObjectsListenerStarted( int listener )
//{
//	if( listener == kEngineObjectsListener )
//	{
//		return s_is_engine_objects_listener_started;
//	}
//	else
//	{
//		return s_is_custom_objects_listener_started;
//	}
//}
//
//void magicalObjectConstruct( void )
//{
//	s_olc_mutex.lock();
//
//	if( s_is_engine_objects_listener_started )
//	{
//		s_engine_objects_listener.construct_count += 1;
//	}
//
//	if( s_is_custom_objects_listener_started )
//	{
//		s_custom_objects_listener.construct_count += 1;
//	}
//
//	s_olc_mutex.unlock();
//}
//
//void magicalObjectDestruct( void )
//{
//	s_old_mutex.lock();
//
//	if( s_is_engine_objects_listener_started )
//	{
//		s_engine_objects_listener.destruct_count += 1;
//	}
//
//	if( s_is_custom_objects_listener_started )
//	{
//		s_custom_objects_listener.destruct_count += 1;
//	}
//
//	s_old_mutex.unlock();
//}
//
//int magicalGetObjectsConstructCount( int listener )
//{
//	if( listener == kEngineObjectsListener )
//	{
//		return s_engine_objects_listener.construct_count;
//	}
//	else
//	{
//		return s_custom_objects_listener.construct_count;
//	}
//}
//
//int magicalGetObjectsDestructCount( int listener )
//{
//	if( listener == kEngineObjectsListener )
//	{
//		return s_engine_objects_listener.destruct_count;
//	}
//	else
//	{
//		return s_custom_objects_listener.destruct_count;
//	}
//}
//#endif

