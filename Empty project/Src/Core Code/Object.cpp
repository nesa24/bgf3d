/*-----------------------------------------+      
|   @@@@@@@@@        @@@@@    @@@@@  @@@@@ |      
|   @@@@@@@@@@     @@@@@@@@   @@@@@  @@@@@ |      
|    @@     @@    @@@    @@@   @@    @@@   |      
|    @@     @@   @@@      @@   @@  @@@     |      
|    @@    @@    @@       @@   @@ @@@      |      
|    @@@@@@@    @@        @@   @@@@@@      |      
|   @@@@@@@@@   @@        @@  @@@@@@@@     |      
|   @@     @@@  @@       @@   @@@  @@@     |      
|   @@      @@  @@      @@@   @@    @@@    |      
|   @@      @@  @@@    @@@    @@     @@    |      
| @@@@@@@@@@@    @@@@@@@@   @@@@@@   @@@@  |      
| @@@@@@@@@@      @@@@@     @@@@@@    @@@  |      
+-----------------------------------------*/

//------------------------------------------------------------
//	Include 
//------------------------------------------------------------
#include "stdafx.h"
#include "Object.h"

//------------------------------------------------------------
//	Implement
//------------------------------------------------------------

//------------------------------------------------------------
Object::Object( void )
{
	// nothing here
	// kyo's Added
	/************************************************************************/
	/* 初始化datagroup                                                                     */
	/************************************************************************/
	memset( m_BaseDataGroup, 0, sizeof(m_BaseDataGroup) );
	memset( m_BaseBoolGroup, 0, sizeof(m_BaseBoolGroup) );

	m_bVisible = true;
	m_fXScale = 1;
	m_fYScale = 1;
	m_iAngle = 0;
	m_posLT.x = -240;
	m_posLT.y = -240;
	m_uiLayer = 0;
	m_indexCurrentPic = 0;
	m_dwColor = 0xffffffff;

}
//------------------------------------------------------------
Object::~Object( void )
{
	// nothing here
}
//------------------------------------------------------------
void Object::SetBoolGroupByIndex( const int index, const bool &value )
{
	// judge the index
	if( index < 0 
		|| 
		index >= sizeof( m_BaseBoolGroup ) / sizeof( bool ) )
	{
		// the index is out of range
		return;
	}
	else
	{
		m_BaseBoolGroup[ index ] = value;
	}


	//Animation special judgment
	if( false == value )
	{
		switch (index)
		{
		case ANIMATION_TYPE_ALPHA:
			SetColorARGB( 255, 255, 255, 255 );
			break;
		}
	}
}
//------------------------------------------------------------
void Object::SetDataGroupByIndex( const int index, const int &value )
{
	// judge the index
	if( index < 0 
		|| 
		index >= sizeof( m_BaseDataGroup ) / sizeof( int ) )
	{
		// the index is out of range
		return;
	}
	else
	{
		m_BaseDataGroup[ index ] = value;
	}
}
//------------------------------------------------------------
void Object::SetEnable( const bool bEnable )
{
	m_bEnable = bEnable;
}
//------------------------------------------------------------
void Object::SetLayer( const unsigned int &uiLayer )
{
	m_uiLayer = uiLayer;
}
//------------------------------------------------------------
void Object::SetPosCenter( const POINT &posCenter )
{
	m_posCenter = posCenter;
}
//------------------------------------------------------------
void Object::SetPosCompare( const POINT &posCompare )
{
	m_posCompare = posCompare;
}
//------------------------------------------------------------
void Object::SetPosLT( const POINT &posLT )
{
	m_posLT = posLT;
}
//------------------------------------------------------------
void Object::SetScale( const float &fXScale, const float &fYScale )
{
	m_fXScale = fXScale;
	m_fYScale = fYScale;
}
//------------------------------------------------------------
void Object::SetSize( const POINT &Size )
{
	if (Size.x < 0
		||
		Size.y < 0)
	{
		return;
	}
	else
	{
		m_Size = Size;
	}
}
//------------------------------------------------------------
void Object::SetVisible( const bool bVisible )
{
	m_bVisible = bVisible;
}
//------------------------------------------------------------
void Object::SetXScale( const float &fXScale )
{
	m_fXScale = fXScale;
}
//------------------------------------------------------------
void Object::SetYScale( const float &fYScale )
{
	m_fYScale = fYScale;
}
//------------------------------------------------------------
void Object::AddPicLocation( const PicLocation &picLocation )
{
	m_vecPicLocation.push_back( picLocation );
}
//------------------------------------------------------------
bool Object::IsHited( const POINT &posMouse )
{
	/************************************************************************/
	/* if it's not visible, return false                                                                     */
	/************************************************************************/
	if ( false == m_bVisible )
		return false;

	if( m_posLT.x < posMouse.x
		&& m_posLT.x + m_Size.x > posMouse.x
		&& m_posLT.y < posMouse.y
		&& m_posLT.y + m_Size.y > posMouse.y)
		return true;
	else
		return false;
}
//------------------------------------------------------------
void Object::LoseFocus( void )
{
	using namespace luabind;
	if (m_strLoseFocusFunc.empty())
		return;
	const char* strFun = m_strLoseFocusFunc.c_str();
	call_function< void >( g_L, strFun );
}
//------------------------------------------------------------
void Object::GetFocus( void )
{
	using namespace luabind;
	if (m_strFocusFunc.empty())
		return;
	const char* strFun = m_strFocusFunc.c_str();
	call_function< void >( g_L, strFun );
}
//------------------------------------------------------------
void Object::MouseDBClick( void )
{
	// nothing till now
}
//------------------------------------------------------------
void Object::MouseIn( void )
{
	// TODO:
	//		Add mouse in effect here
}
//------------------------------------------------------------
void Object::MouseLClick( void )
{
	// TODO:
	//		Add mouse left click codes here
}
//------------------------------------------------------------
void Object::MouseRClick( void )
{
	// TODO:
	//		Add mouse right click codes here
}
//------------------------------------------------------------
void Object::KeyDown( const WPARAM &wKey )
{
	// TODO:
	//		do nothing in the base class
}
//------------------------------------------------------------
Object *Object::CreateObject( void )
{
	return new Object;
}
//------------------------------------------------------------
void Object::SetPicIndex( unsigned int index )
{
//	assert( index < m_vecPicLocation.size() );
	m_indexCurrentPic = index;
}
//--------------------------------------------------
bool Object::Draw(Canvas* pCanvas)
{
	if ( pCanvas )
	{
		pCanvas->DrawObject( this );
	}
	return true;
}
//--------------------------------------------------
void Object::SetFocusFunc(string strFunc )
{
	m_strFocusFunc = strFunc;
}
//--------------------------------------------------
void Object::SetLoseFocusFunc(string strFunc )
{
	m_strLoseFocusFunc = strFunc;
}
//--------------------------------------------------
void Object::LogicKeyDown()
{
	//在这里添加有关按键的处理
}
