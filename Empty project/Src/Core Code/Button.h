#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include "ObjUI.h"
#include <vector>

class ObjButton : public ObjUI
{
public:
	~ObjButton( void ){};
	ObjectType GetObjectType( void ) const;
	static Object* CreateObject( void )
	{
		return (Object*)new ObjButton;
	}
	void MouseLClick( void );
	void GetFocus( void );
	void LoseFocus( void );
	void SetFun( std::string strFun );
	void PushStrParam( std::string strValue );
	void PushIntParam( int iValue );
protected:
	ObjButton( void ){};
	std::string m_strFun;
	std::vector< std::string >	m_vecStrParam;
	std::vector< int >			m_vecIntParam;
};

#endif
