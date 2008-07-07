/*!
* CopyRight \b (c) 2006 BOKteam
* All Rights Reserved
*
* \file Panel.h
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

#if !defined(AFX_PANEL_H__FACE7B3A_92F9_4EB9_AA44_2B1E4E689C5D__INCLUDED_)
#define AFX_PANEL_H__FACE7B3A_92F9_4EB9_AA44_2B1E4E689C5D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Object.h"
#include "Enumerate.h"
#include <list>
#include <windows.h>

using namespace std;

/*!
* \class Panel
* \brief All Window in the game 
*
* Attention Every panel has a ID
*/
class Panel : public Object  
{
public:
	list< Object* >& GetObjectList();
	bool PanelMove( POINT pos );
	bool InitPanelPic();
	bool TryToSelect();
	bool Init();
	bool Draw( Canvas* pCanvas );
	void LogicKeyDown();
	void CharInput( UINT nChar );
	Object* GetHitedItem( const POINT &posMouse );

	bool AddObject( Object* pObject );
	bool ClearObject( Object* pObject );
	bool TidyObjects();
	void ClearAll();

	virtual void MouseLClick(void){};
	virtual ObjectType GetObjectType() const;
	virtual void RealTimeLogic(void){/*Do nothing in the base class*/};
	virtual void MouseClickAt( const POINT &posMouse );
	virtual void MouseMoveAt( const POINT &posMouse );
	virtual void KeyDown( const WPARAM &wKey );

	void SetName( std::string strName );
	std::string GetName( void );

	Panel( void );
	Panel(const char* pName, POINT PosLT, POINT PosSize);
	virtual ~Panel();

	//Object Create fun
	static Object *CreateObject( void );

protected:
	std::string m_strName;
	Object* m_objFocusedObject;
	list<Object*> m_Objects;
};

#endif // !defined(AFX_PANEL_H__FACE7B3A_92F9_4EB9_AA44_2B1E4E689C5D__INCLUDED_)
