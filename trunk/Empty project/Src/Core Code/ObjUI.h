#ifndef OBJECT_UI_H
#define OBJECT_UI_H

#include "Object.h"

#include <string>
using namespace std;

class ObjUI : public Object
{
public:
	~ObjUI( void ){};
	virtual ObjectType GetObjectType( void )
	{
		return ObjectUI;
	}
	static Object* CreateObject( void )
	{
		return NULL;
	}
	virtual void SetName( string name )
	{
		m_strName = name;
	}

	virtual string GetName()
	{
		return m_strName;
	}

protected:
	ObjUI( void ){};

	string m_strName;
};

#endif
