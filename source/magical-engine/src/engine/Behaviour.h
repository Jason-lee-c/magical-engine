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
#ifndef __BEHAVIOUR_H__
#define __BEHAVIOUR_H__

#include "magical-macros.h"
#include "Common.h"
#include "Reference.h"

NAMESPACE_MAGICAL

class BehaviourFeature : public Reference
{
public:
	virtual void onCreate( void ){}
	virtual void onStart( void ){}
	virtual void onUpdate( void ){}
	virtual void onStop( void ){}
	virtual void onDestroy( void ){}
};

template< class Ty >
class Behaviour : public BehaviourFeature
{
protected:
	friend class Entity;
	Ty* object = nullptr;
};

NAMESPACE_END

#endif //__BEHAVIOUR_H__