#include "StdAfx.h"
#include "Button.h"

//--------------------------------------------------
ObjectType ObjButton::GetObjectType( void ) const
{
	return ObjectButton;
}
//--------------------------------------------------
void ObjButton::MouseLClick( void )
{
	// TODO: if mouse clicked...
	using namespace luabind;
	const char* strFun = m_strFun.c_str();
	call_function< void >( g_L, strFun );

	//special mouse click process
	//the code below will be different between different games
}
//--------------------------------------------------
void ObjButton::GetFocus( void )
{
	//// TODO: get focus, change the image of button
	//// there are 2 pictures for one button, index 0 picture is normal
	//// picture, and index 1 picture is the focused picture.
	m_indexCurrentPic = 1;
	//g_pAudio->SetSoundVolume( 0, 50 );
	//g_pAudio->PlayGameSound( 0 );
	Object::GetFocus();
}
//--------------------------------------------------
void ObjButton::LoseFocus( void )
{
	//// TODO: lose focus, change the image of button
	m_indexCurrentPic = 0;
	Object::LoseFocus();
}
//--------------------------------------------------
void ObjButton::SetFun( std::string strFun )
{
	m_strFun = strFun;
}
//--------------------------------------------------
void ObjButton::PushStrParam( std::string strValue )
{
	m_vecStrParam.push_back( strValue );
}
//--------------------------------------------------
void ObjButton::PushIntParam( int iValue )
{
	m_vecIntParam.push_back( iValue );
}
//--------------------------------------------------
