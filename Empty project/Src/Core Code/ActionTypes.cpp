/**
	Implement of action types.
 */

#include "StdAfx.h"
#include "ActionTypes.h"
#include <assert.h>

//--------------Action Base-------------------------
//--------------------------------------------------
ActionBase::ActionBase( void )
{
}
//--------------------------------------------------
ActionBase::~ActionBase( void )
{
}
//--------------------------------------------------
bool ActionBase::Do( void )
{
	return false;
}
//--------------------------------------------------
string ActionBase::GetPhaseName( void )
{
	return m_strPhaseName;
}
//--------------------------------------------------
void ActionBase::SetPhaseName( const char* name )
{
	m_strPhaseName = name;
}
//--------------------------------------------------

//--------------Action ChangePhase------------------
//--------------------------------------------------
ActChangePhase::ActChangePhase( void )
{
}
//--------------------------------------------------
ActChangePhase::ActChangePhase( const char* strTargetPhase )
{
	m_strTargetPhase = strTargetPhase;
}
//--------------------------------------------------
ActChangePhase::~ActChangePhase( void )
{
	// nothing here
}
//--------------------------------------------------
bool ActChangePhase::Do( void )
{
	// TODO:
	//		Add action change phase codes here.
	return false;
}
//--------------------------------------------------

//--------------Act Exit----------------------------
//--------------------------------------------------
ActExit::ActExit( void )
{
}
//--------------------------------------------------
ActExit::~ActExit( void )
{
}
//--------------------------------------------------
bool ActExit::Do( void )
{
	xTrace( "ActExit::Do" );
	exit( 0 );
	return true;
}
//--------------------------------------------------

//-------------Action UI----------------------------
//--------------------------------------------------
ActionUI::ActionUI( void )
{
}
//--------------------------------------------------
ActionUI::~ActionUI( void )
{
}
//--------------------------------------------------
bool ActionUI::Do( void )
{
	return true;
}
//--------------------------------------------------

//---------------Action Logic-----------------------
//--------------------------------------------------
ActionLogic::ActionLogic( void )
{
}
//--------------------------------------------------
ActionLogic::~ActionLogic( void )
{
}
//--------------------------------------------------
bool ActionLogic::Do( void )
{
	return true;
}
//--------------------------------------------------

//--------------Action left mouse click-------------
//--------------------------------------------------
ActLClick::ActLClick( void )
{
}
//--------------------------------------------------
ActLClick::ActLClick( const POINT& posMouse )
{
	m_posMouse = posMouse;
}
//--------------------------------------------------
ActLClick::~ActLClick( void )
{
}
//--------------------------------------------------
bool ActLClick::Do( void )
{
	// TODO: remove the sprit object
	singPhaseManager::instance().GetCurrentPhase()->MouseClickAt( m_posMouse );
	return true;
}
//--------------------------------------------------

//------------Action Mouse Move --------------------
//--------------------------------------------------
ActMouseMove::ActMouseMove( void )
{
}
//--------------------------------------------------
ActMouseMove::ActMouseMove( const POINT& posMouse )
{
	m_posMouse = posMouse;
}
//--------------------------------------------------
ActMouseMove::~ActMouseMove( void )
{
}
//--------------------------------------------------
bool ActMouseMove::Do( void )
{
	Phase* ptrPhase = singPhaseManager::instance().GetCurrentPhase();
	//calling mouse move funs
	ptrPhase->MouseMoveAt( m_posMouse );

	//update phase focused object
	Panel* ptrPanel = ptrPhase->GetHitedPanel( m_posMouse );
	if (!ptrPanel)
	{
		//release object if null panel selected
		ptrPhase->ReleaseFocusObject();
		return true;
	}

	Object* ptrObj = ptrPanel->GetHitedItem( m_posMouse );
	if (!ptrObj)
	{
		//release object if null object selected
		ptrPhase->ReleaseFocusObject();
		return true;
	}

	Object* ptrFocus = ptrPhase->GetFocusObject();
	//focus on same object, return
	if (ptrObj == ptrFocus)
		return true;
	//object unfocusable, return
	if( !ptrObj->GetFocusable() )
		return true;

	if (ptrObj && !ptrFocus)
	{
		ptrObj->GetFocus();
		ptrPhase->SetFocusObject( ptrObj );
	}
	else if (ptrObj && ptrFocus)
	{
		ptrFocus->LoseFocus();
		ptrObj->GetFocus();
		ptrPhase->SetFocusObject( ptrObj );
	}
	return true;
}
//--------------------------------------------------


//------------Action Key down --------------------
//--------------------------------------------------
ActKeyDown::ActKeyDown( void )
{
}
//--------------------------------------------------
ActKeyDown::ActKeyDown( const WPARAM Key )
{
	m_wKey = Key;
}
//--------------------------------------------------
ActKeyDown::~ActKeyDown( void )
{
}
//--------------------------------------------------
bool ActKeyDown::Do( void )
{
	// TODO: remove the sprit object
	singPhaseManager::instance().GetCurrentPhase()->KeyDown( m_wKey );
	return true;
}
//--------------------------------------------------
ActCharInput::ActCharInput( void )
{
}
//--------------------------------------------------
ActCharInput::ActCharInput( const WPARAM Key )
{
	m_wKey = Key;
}
//--------------------------------------------------
ActCharInput::~ActCharInput( void )
{
}
//--------------------------------------------------
bool ActCharInput::Do( void )
{
	singPhaseManager::instance().GetCurrentPhase()->CharInput( m_wKey );
	return true;
}
