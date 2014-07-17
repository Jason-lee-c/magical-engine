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
<<<<<<< HEAD:source/magical-common/src/file/win32/FileSystem.cpp
#include "PlatformMacros.h"
#include "FileSystem.h"
=======
#include "AssetsSystem.h"

#include <windows.h>
#include <cstring>

<<<<<<< HEAD
>>>>>>> origin/master:source/magical-common/src/assets/win32/AssetsSystem.cpp
#include "Common.h"

#include <windows.h>
=======
#include "Utils.h"
#include "Array.h"
#include "Map.h"
>>>>>>> ec1b54020335b76df015817be9eeaa46104a0857

static Map<std::string, std::string> s_absolute_path_cache_map;
static Array<std::string> s_search_path_array;
static std::string s_default_search_path;

static std::string win32GetPathWithUnixStyle( const char* path );
static std::string win32GetAssetsDefaultSearchPath( void );
static std::string win32GetAbsloutePath( const char* path );


void AssetsSystem::init( void )
{
	s_default_search_path = win32GetAssetsDefaultSearchPath();
	if( s_default_search_path.empty() )
	{
		magicalSetLastErrorInfo("default_search_path is empty, win32GetAssetsDefaultSearchPath() error");
		magicalLogLastError();
		return;
	}
	s_search_path_array.push_back( s_default_search_path );
}

void AssetsSystem::delc( void )
{
	
}

<<<<<<< HEAD:source/magical-common/src/file/win32/FileSystem.cpp
void FileSystem::addSearchPath( const std::string& path )
{
	std::string unix_path = std::move( win32ConvertPathFormatToUnixStyle( path ) );
	std::string prefix;
	if( isAbsolutePath( unix_path ) == false )
=======
void AssetsSystem::addSearchPath( const char* path )
{
	magicalAssert( path, "should not be nullptr" );

	std::string unix_path = win32GetPathWithUnixStyle( path );
	std::string prefix;
	if( FileUtils::isAbsolutePath( unix_path.c_str() ) == false )
>>>>>>> origin/master:source/magical-common/src/assets/win32/AssetsSystem.cpp
	{
		prefix = s_default_search_path;
	}

	std::string real_path = std::move( prefix + unix_path );
	if( real_path.length() > 0 && real_path[real_path.length() - 1] != '/' )
	{
		real_path += "/";
	}
	s_search_path_array.push_back( real_path );
	s_absolute_path_cache_map.clear();
}

<<<<<<< HEAD:source/magical-common/src/file/win32/FileSystem.cpp
void FileSystem::removeSearchPath( const std::string& path )
{
	std::string unix_path = std::move( win32ConvertPathFormatToUnixStyle( path ) );
=======
void AssetsSystem::removeSearchPath( const char* path )
{
	magicalAssert( path, "should not be nullptr" );

	std::string unix_path = win32GetPathWithUnixStyle( path );
>>>>>>> origin/master:source/magical-common/src/assets/win32/AssetsSystem.cpp
	auto path_itr = std::find( s_search_path_array.begin(), s_search_path_array.end(), unix_path );
	if( path_itr != s_search_path_array.end() )
	{
		s_search_path_array.erase( path_itr );
		s_absolute_path_cache_map.clear();
	}
}

<<<<<<< HEAD:source/magical-common/src/file/win32/FileSystem.cpp
bool FileSystem::isAbsolutePath( const std::string& path )
{
	if( path.length() > 2
		&& ((path[0] >= 'a' && path[0] <= 'z') 
		|| ( path[0] >= 'A' && path[0] <= 'Z'))
		&& ( path[1] == ':') )
	{
		return true;
	}
	return false;
}

bool FileSystem::isFileExist( const std::string& file )
=======
void AssetsSystem::clearSearchPath( void )
{
	s_search_path_array.clear();
	s_absolute_path_cache_map.clear();
}

bool AssetsSystem::isAssetsFileExist( const char* file_name )
>>>>>>> origin/master:source/magical-common/src/assets/win32/AssetsSystem.cpp
{
	magicalAssert( file_name, "should not be nullptr" );

<<<<<<< HEAD:source/magical-common/src/file/win32/FileSystem.cpp
	std::string file_path = std::move( win32ConvertPathFormatToUnixStyle( file ) );
	if( isAbsolutePath( file_path ) == false )
=======
	std::string file_path = win32GetPathWithUnixStyle( file_name );
	if( FileUtils::isAbsolutePath( file_path.c_str() ) == false )
>>>>>>> origin/master:source/magical-common/src/assets/win32/AssetsSystem.cpp
	{
		std::string abs_path;
		for( const auto& prefix : s_search_path_array )
		{
			abs_path = std::move( prefix + file_path );
			int ret = GetFileAttributesA( abs_path.c_str() );
			if( ret != -1 )
			{
				return true;
			}
		}
	}
	else
	{
		return GetFileAttributesA( file_path.c_str() ) != -1 ? true : false;
	}

	return false;
}

<<<<<<< HEAD
<<<<<<< HEAD:source/magical-common/src/file/win32/FileSystem.cpp
const std::string FileSystem::toAbsolutePath( const std::string& path )
{
	if( isAbsolutePath( path ) )
	{
		return path;
	}
	std::string unix_path = win32ConvertPathFormatToUnixStyle( path );

	auto cache_itr = s_absolute_path_cache_map.find( unix_path );
	if( cache_itr != s_absolute_path_cache_map.end() )
	{
		return cache_itr->second;
	}

	std::string abs_path;
	for( const auto& prefix : s_search_path_array )
	{
		abs_path = std::move( prefix + unix_path );
		int ret = GetFileAttributesA( abs_path.c_str() );
		if( ret != -1 )
		{
			s_absolute_path_cache_map.insert( std::make_pair(unix_path, abs_path) );
			return std::move( abs_path );
		}
	}
	return "";
}

const std::vector<std::string>& FileSystem::getSearchPaths( void )
{
	return s_search_path_array;
}



static std::string win32ConvertPathFormatToUnixStyle( const std::string& path )
=======
Data AssetsSystem::getAssetsFile( const char* file_name )
=======
Data* AssetsSystem::getAssetsFile( const char* file_name )
>>>>>>> ec1b54020335b76df015817be9eeaa46104a0857
{
	magicalAssert( file_name, "should not be nullptr" );

	std::string abs_path = win32GetAbsloutePath( file_name );
	magicalAssert( !abs_path.empty(), StringUtils::format<512>("get assets file data failed! file(%s) doesn't exist!", file_name).c_str() );

	FILE* fp = fopen( abs_path.c_str(), "rb" );
	if( fp == nullptr )
	{
		magicalSetLastErrorInfo( StringUtils::format<512>("get assets file data failed! file(%s)", file_name).c_str() );
		magicalLogLastError();
		return nullptr;
	}

	size_t size, read_size = 0;
	fseek( fp, 0, SEEK_END );
	size = (size_t) ftell( fp );
	fseek( fp, 0, SEEK_SET );

	Data* data = Data::create();
	data->malloc( size + 1 );

	read_size = fread( data->ptr(), sizeof(char), size, fp );
	data->realloc( read_size + 1 );
	data->ptr()[ read_size ] = 0;

	fclose( fp );
	
	return std::move( data );
}

static std::string win32GetPathWithUnixStyle( const char* path )
>>>>>>> origin/master:source/magical-common/src/assets/win32/AssetsSystem.cpp
{
    std::string ret = path;
    int len = ret.length();
    for( int i = 0; i < len; ++i )
    {
        if( ret[i] == '\\' )
        {
            ret[i] = '/';
        }
    }
    return std::move( ret );
}

static std::string win32GetAssetsDefaultSearchPath( void )
{
	char buf[kMaxPathLength] = {0};
	GetCurrentDirectoryA( sizeof(buf)-1, buf );

<<<<<<< HEAD:source/magical-common/src/file/win32/FileSystem.cpp
	std::string ret = win32ConvertPathFormatToUnixStyle( std::move(std::string(buf)) );
	ret.append("/");
	return std::move(ret);
=======
	std::string ret = win32GetPathWithUnixStyle( buf );
	ret.append( "/" );
	return std::move( ret );
}

std::string win32GetAbsloutePath( const char* path )
{
	magicalAssert( path, "should not be nullptr" );

	if( FileUtils::isAbsolutePath(path) )
	{
		return path;
	}
	std::string unix_path = win32GetPathWithUnixStyle( path );

	auto cache_itr = s_absolute_path_cache_map.find( unix_path );
	if( cache_itr != s_absolute_path_cache_map.end() )
	{
		return cache_itr->second;
	}

	std::string abs_path;
	for( const auto& prefix : s_search_path_array )
	{
		abs_path = prefix + unix_path;
		int ret = GetFileAttributesA( abs_path.c_str() );
		if( ret != -1 )
		{
			s_absolute_path_cache_map.insert( std::make_pair(unix_path, abs_path) );
			return std::move( abs_path );
		}
	}
	return "";
>>>>>>> origin/master:source/magical-common/src/assets/win32/AssetsSystem.cpp
}