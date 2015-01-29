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
#ifndef __SCENE_NODE_H__
#define __SCENE_NODE_H__

#include "PlatformMacros.h"
#include "Common.h"
#include "Reference.h"
#include "magical-math.h"
#include <vector>

NS_MAGICAL_BEGIN

using ::std::string;
using ::std::vector;

enum class Space 
{
	Self,
	Parent,
	World,
};

class SceneNode : public Reference
{
public:
	declare_class_hash_code;

public:
	SceneNode( void );
	virtual ~SceneNode( void );

public:
	void setName( const char* name );
	const string& getName( void ) const;
	void setVisible( bool visible );
	bool isVisible( void ) const;

public:
	bool isChildOf( const Ptr<SceneNode>& parent ) const;
	size_t childCount( void ) const;
	SceneNode* getParent( void ) const;
	SceneNode* findChild( const char* name ) const;
	SceneNode* childAtIndex( size_t i ) const;
	void addChild( const Ptr<SceneNode>& child );
	void setParent( const Ptr<SceneNode>& parent );
	void removeChild( const Ptr<SceneNode>& child );
	void removeAllChildren( void );
	void removeSelf( void );

public:
	void translate( const Vector2& t, Space relative_to = Space::Parent );
	void translate( const Vector3& t, Space relative_to = Space::Parent );
	void translate( float x, float y, Space relative_to = Space::Parent );
	void translate( float x, float y, float z, Space relative_to = Space::Parent );
	void setPosition( const Vector2& t );
	void setPosition( const Vector3& t );
	void setPosition( float x, float y );
	void setPosition( float x, float y, float z );
	const Vector3& getPosition( void ) const;

public:
	void yaw( float yaw, Space relative_to = Space::Self );
	void pitch( float pitch, Space relative_to = Space::Self );
	void roll( float roll, Space relative_to = Space::Self );
	void lookAt( const Vector3& target, const Vector3& up );
	void rotate( const EulerAngles& r, Space relative_to = Space::Self );
	void rotate( const Quaternion& r, Space relative_to = Space::Self );
	void rotate( float yaw, float pitch, float roll, Space relative_to = Space::Self );
	void setRotation( const EulerAngles& r );
	void setRotation( const Quaternion& r );
	void setRotation( float yaw, float pitch, float roll );
	const Quaternion& getRotation( void ) const;

public:
	void scale( const Vector2& s );
	void scale( const Vector3& s );
	void scale( float x, float y );
	void scale( float x, float y, float z );
	void scale( float s );
	void setScale( const Vector2& s );
	void setScale( const Vector3& s );
	void setScale( float x, float y );
	void setScale( float x, float y, float z );
	const Vector3& getScale( void ) const;

protected:
	virtual void onAdd( SceneNode* child );
	virtual void onRemove( const vector<SceneNode*>& children );
	virtual void onRemove( SceneNode* child );
	
protected:
	void transform( void );
	void transformDirty( int info );
	const Vector3& getDerivedPosition( void ) const;
	const Quaternion& getDerivedRotation( void ) const;
	const Vector3& getDerivedScale( void ) const;

protected:
	friend class Scene;

protected:
	string m_name;
	bool m_is_visible = false;
	SceneNode* m_parent = nullptr;
	vector<SceneNode*> m_children;
	bool m_inherit_scale = true;
	bool m_inherit_rotation = true;
	mutable int m_ts_dirty_info;
	bool m_ts_dirty = false;
	Vector3 m_local_position;
	Quaternion m_local_rotation;
	Vector3 m_local_scale = Vector3::One;
	Matrix4 m_local_to_world_matrix;
	mutable Vector3 m_derived_position;
	mutable Quaternion m_derived_rotation;
	mutable Vector3 m_derived_scale = Vector3::One;
};

NS_MAGICAL_END

#endif //__SCENE_NODE_H__