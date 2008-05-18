#ifndef OBJECT_IMAGE_H
#define OBJECT_IMAGE_H 

#include "ObjUI.h"

class Image : public ObjUI
{
public:
	virtual ~Image( void ){};
	ObjectType GetObjectType( void ) const
	{
		return ObjectStaticImage;
	}
	static Object* CreateObject( void )
	{
		return (Object*) new Image;
	}
protected:
	Image( void ){};
};

#endif
