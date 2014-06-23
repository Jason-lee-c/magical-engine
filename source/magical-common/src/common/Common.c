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
#include "PlatformMacros.h"
#include "Common.h"

#define kMaxLogLength 1024 * 16

static int s_last_error = false;
static char* s_last_error_info = NULL;
static struct timeval s_tv_ticking;

#ifdef MAG_DEBUG
int g_is_observing = false;
int g_observer_construct_count = 0;
int g_observer_destruct_count = 0;
#endif

MAGAPI_USER void magicalLogImpl( const char* str )
{
#ifdef MAG_WIN32
    OutputDebugStringA(str);
    OutputDebugStringA("\n");
	printf("%s\n", str);
#endif
}

MAGAPI_USER void magicalLogFormatImpl( const char* format, ... )
{
	char buf[kMaxLogLength];

	va_list args;
	va_start(args, format);
	vsnprintf(buf, kMaxLogLength, format, args);
	va_end(args);

	magicalLogImpl(buf);
}

MAGAPI void magicalReportImpl( const char* str, const char* function, int line )
{
	char buf[kMaxLogLength];

	struct tm tm_now;
	time_t now;
	
	time(&now);
	tm_now = *localtime(&now);

	sprintf(buf, "[Report %d/%02d/%02d %02d:%02d:%02d]: %s  %s:%d", 
		tm_now.tm_year + 1900,
		tm_now.tm_mon + 1,
		tm_now.tm_mday,
		tm_now.tm_hour,
		tm_now.tm_min,
		tm_now.tm_sec,
		str,
		function, 
		line
		);

	magicalLog(buf);
}

MAGAPI int magicalIsError( void )
{
	return s_last_error;
}

MAGAPI void magicalIgnoreLastError( void )
{
	s_last_error = false;
}

MAGAPI const char* magicalSetLastErrorInfo( const char* info )
{
	if( s_last_error_info )
	{
		free(s_last_error_info);
	}

	s_last_error_info = (char*) malloc(strlen(info) + 1);
	strcpy(s_last_error_info, info);

	s_last_error = true;

	return magicalGetLastErrorInfo();
}

MAGAPI const char* magicalGetLastErrorInfo( void )
{
	if( s_last_error_info )
	{
		return s_last_error_info;
	}
	else
	{
		return "none";
	}
}

#ifdef MAG_WIN32
extern int gettimeofday( struct timeval* tv, struct timezone* tz )
{
	LARGE_INTEGER time, freq;
	if( tv != NULL )
    {
        QueryPerformanceFrequency( &freq );
        QueryPerformanceCounter( &time );
        tv->tv_sec  = (long)( time.QuadPart / freq.QuadPart );
        tv->tv_usec = (long)( time.QuadPart * 1000000.0 / freq.QuadPart - tv->tv_sec * 1000000.0 );
    }
	return 0;
}
#endif

MAGAPI_USER void magicalGetTimeOfDay( struct timeval* tv, struct timezone* tz )
{
	if( gettimeofday(tv, tz) != 0 )
	{
		magicalSetLastErrorInfo(magicalTagError("gettimeofday(tv, tz)"));
		magicalReportLastError();
	}
}

MAGAPI void magicalBeginTicking( void )
{
	magicalGetTimeOfDay(&s_tv_ticking, NULL);
}

MAGAPI float magicalEndTicking( void )
{
	struct timeval tv_now;
	float  result;

	magicalGetTimeOfDay(&tv_now, NULL);
	result = (tv_now.tv_sec - s_tv_ticking.tv_sec) + (tv_now.tv_usec - s_tv_ticking.tv_usec) / 1000000.0f;
	result = MAX(0.0f, result);

	return result;
}

//#ifdef MAG_DEBUG
//MAGAPI void magicalBeginObserveObject()
//{
//	//char buf[256];
//	//const char* info;
//	s_is_observing = true;
//	s_observer_construct_count = 0;
//	s_observer_destruct_count = 0;
//
//	magicalReport("Observe Object Begin : ");
//}
//
//MAGAPI void magicalEndObserveObject()
//{
//	char buf[256];
//	sprintf(buf, "Observe Object Ended : construct=%d destruct=%d", s_observer_construct_count, s_observer_destruct_count);
//	s_is_observing = false;
//	
//	magicalReport(buf);
//}
//
//MAGAPI void magicalObjectConstruct()
//{
//	if( s_is_observing )
//	{
//		++ s_observer_construct_count;
//	}
//}
//
//MAGAPI void magicalObjectDestruct()
//{
//	if( s_is_observing )
//	{
//		++ s_observer_destruct_count;
//	}
//}
//#endif