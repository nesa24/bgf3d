#pragma once
#include "object.h"

class Sprite :
	public Object
{
public:
	Sprite(void);
	virtual ~Sprite(void);
public:
	virtual void MouseLClick(void){};
	virtual ObjectType GetObjectType( void ) const;
	//Object Create fun
	static Object *CreateObject( void );


};
