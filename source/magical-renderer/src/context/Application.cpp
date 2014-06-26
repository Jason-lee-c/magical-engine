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
#include "Application.h"
#include "Common.h"
#include "Engine.h"
#include "LuaSystem.h"

#include "glut/glut.h"

static EventOnFinishLaunching s_on_finish_launching_callback = nullptr;

static bool magicalWin32SetupGL( void )
{
	GLenum result;

	result = glewInit();
	if( result != GLEW_OK )
	{
		magicalSetLastErrorInfo("init glew error");
		magicalReportLastError();
		return false;
	}

	return true;
}

static bool magicalWin32ShutdownGL( void )
{
	return true;
}

static void magicalWin32GlutReshape( int w, int h )
{ 
	magicalOnReshape(w, h);
}

static void magicalWin32GlutRender( void )
{
	magicalOnRender();

	glutSwapBuffers();
	glutPostRedisplay();
}

MAGAPI_USER void magicalApplicationInit( EventOnFinishLaunching callback )
{
	s_on_finish_launching_callback = callback;
}

MAGAPI_USER void magicalRun( void )
{
	GLint argc = 0;

	glutInit(&argc, NULL);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(960, 640);
	glutCreateWindow("Magical Engine");

	glutReshapeFunc(magicalWin32GlutReshape);
	glutDisplayFunc(magicalWin32GlutRender);

	if( magicalWin32SetupGL() == false )
	{
		MessageBoxA(NULL, magicalGetLastErrorInfo(), "Error", MB_OK);
		return;
	}

	magicalEngineInit();
	if( magicalEngineInitSystems() == false )
	{
		MessageBoxA(NULL, magicalGetLastErrorInfo(), "Error", MB_OK);
		return;
	}

	s_on_finish_launching_callback();

	glutMainLoop();

	if( magicalEngineDelcSystems() == false )
	{
		MessageBoxA(NULL, magicalGetLastErrorInfo(), "Error", MB_OK);
		return;
	}
	magicalEngineDelc();

	if( magicalWin32ShutdownGL() == false )
	{
		MessageBoxA(NULL, magicalGetLastErrorInfo(), "Error", MB_OK);
		return;
	}
}
