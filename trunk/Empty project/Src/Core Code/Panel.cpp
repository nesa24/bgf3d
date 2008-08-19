/*!
* CopyRight \b (c) 2006 BOKteam
* All Rights Reserved
*
* \file Panel.cpp
*
* This file is a test of doxygen Qt format
*
* \author ly's BOK
* 
* \data April 3, 2006
*
* \version 0.0.1
*
* \warning This is the warning message
*
* \b Modify
*
* \b History
*
*/

#include "stdafx.h"
#include "Panel.h"
#include "CallHit.h"
#include <vector>
#include <list>
#include <algorithm>


ObjectType Panel::GetObjectType() const
{
	return ObjectPanel;
}



//////////////////////////////
//Method to Set the LT position of every object in the panel
//////////////////////////////

bool Panel::TidyObjects()
{


	return true;
}

//bool Panel::AddObject( Object* pObject, POINT ComparePos )
//{
//	m_Objects.push_back( pObject );
//	return true;
//}

bool Panel::AddObject( Object* pObject )
{
	if( NULL == pObject )
		return false;

	m_Objects.push_back( pObject );
	return true;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Panel::Panel( void )
{
	m_objFocusedObject = NULL;
}

Panel::Panel(const char* pName, POINT PosLT, POINT PosSize)
{
	m_objFocusedObject = NULL;
}

Panel::~Panel()
{
	ClearAll();
}

list< Object* >& Panel::GetObjectList()
{
	return m_Objects;
}

bool Panel::ClearObject( Object* pObject )
{
	list< Object * >::iterator iter = find(m_Objects.begin(), m_Objects.end(), pObject);
	if ( m_Objects.end() != iter)
	{
		(*iter) = NULL;
		m_Objects.erase(iter);
		return true;
	}
	else
	{
		return false;
	}
}

Object *Panel::CreateObject( void )
{
	return new Panel;
}

void Panel::SetName( std::string strName )
{
	m_strName = strName;
}

std::string Panel::GetName( void )
{
	return m_strName;
}

bool Panel::Draw( Canvas* pCanvas )
{
	//don't display invisible panel and its item
	if( false == GetVisible() )
		return false;

	list<Object*>::iterator itr;
	list<Object*>::iterator itr_end = m_Objects.end();
	for ( itr = m_Objects.begin(); itr != itr_end; ++itr )
	{
		(*itr)->Draw( pCanvas );
	}
	return true;
}

Object* Panel::GetHitedItem( const POINT &posMouse )
{
	typedef CallHit< Object > ObjectHitTest;
	ObjectHitTest result = for_each( m_Objects.begin(),
		m_Objects.end(), ObjectHitTest( posMouse ) );
	if (!result.m_hitedObject)
		return NULL;
	else
		return result.m_hitedObject;
}

void Panel::MouseClickAt(const POINT &posMouse )
{
	CallHit< Object > pObj =
		for_each( m_Objects.begin(), m_Objects.end(), CallHit< Object >( posMouse ) );
	if (pObj.m_hitedObject)
	{
		if ( m_objFocusedObject )
		{
			if ( ObjectEditBox == m_objFocusedObject->GetObjectType() )
			{
				((EditBox*)m_objFocusedObject)->SetLock( true );
			}
		}

		m_objFocusedObject = pObj.m_hitedObject;
		pObj.m_hitedObject->MouseLClick();
	}
}

void Panel::MouseMoveAt(const POINT &posMouse )
{
	//do nothing in base class
}

void Panel::KeyDown(const WPARAM &wKey )
{
	if( NULL == m_objFocusedObject )
		return;

	m_objFocusedObject->KeyDown( wKey );
}

void Panel::RealTimeLogic(void)
{
	//suppose to run all RTL in all involved object
	list<Object*>::iterator itr;
	list<Object*>::iterator itr_end = m_Objects.end();
	for ( itr = m_Objects.begin(); itr != itr_end; ++itr )
	{
		(*itr)->RealTimeLogic();
	}
}

void Panel::ClearAll()
{
	list<Object*>::iterator iter_each = m_Objects.begin();
	list<Object*>::iterator iter_end = m_Objects.end();
	for( ;iter_each != iter_end; )
	{
		//delete Object
		delete (*iter_each);
		(*iter_each) = NULL;
		
		//erase object
		iter_each = m_Objects.erase( iter_each );
	}
}

void Panel::LogicKeyDown()
{
	list<Object*>::iterator itr;
	list<Object*>::iterator itr_end = m_Objects.end();
	for ( itr = m_Objects.begin(); itr != itr_end; ++itr )
	{
		(*itr)->LogicKeyDown();
	}
}

void Panel::CharInput( UINT nChar )
{
//	list<Object*>::iterator itr;
//	list<Object*>::iterator itr_end = m_Objects.end();
//	for ( itr = m_Objects.begin(); itr != itr_end; ++itr )
//	{
//		if ( ObjectEditBox == (*itr)->GetObjectType() )
//		{
//			((EditBox*)(*itr))->GetChar( nChar );
//			((EditBox*)(*itr))->UpdateData();
//		}
//	}
	if( NULL == m_objFocusedObject )
		return;

	if ( ObjectEditBox == m_objFocusedObject->GetObjectType() )
	{
		((EditBox*)m_objFocusedObject)->GetChar( nChar );
		((EditBox*)m_objFocusedObject)->UpdateData();
	}
}