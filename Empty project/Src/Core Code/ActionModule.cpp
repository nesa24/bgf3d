/**
	Implement of class ActionGenerate
 */

#include "StdAfx.h"
#include "ActionModule.h"
#include <list>
#include <algorithm>

//--------------------------------------------------
ActionModule::ActionModule( void )
{
}
//--------------------------------------------------
ActionModule::~ActionModule( void )
{
}
//--------------------------------------------------
ActionBase* ActionModule::LClickAction( POINT pos )
{
	return new ActLClick( pos );
}
//--------------------------------------------------
ActionBase* ActionModule::MouseMoveAction( POINT pos )
{
	return new ActMouseMove( pos );
}
//--------------------------------------------------
ActionBase* ActionModule::KeyDownAction( WPARAM Key )
{
	return new ActKeyDown( Key );
}

ActionBase* ActionModule::CharInputAction( WPARAM Key )
{
	return new ActCharInput( Key );
}

//--------------------------------------------------
void ActionModule::Process( void )
{
	while (!m_actionQueue.empty())
	{
		ActionBase* action = m_actionQueue.front();
		action->Do();
		SAFE_DELETE(action);
		m_actionQueue.pop();
	}
}
//--------------------------------------------------
void ActionModule::Generate( InputType input, WPARAM wParam, LPARAM lParam )
{
	ActionBase *ptrAction = NULL;
	POINT MousePos;
	MousePos.x = LOWORD( lParam );
	MousePos.y = HIWORD( lParam );

	switch( input )
	{
	case MouseClick:
		ptrAction = LClickAction( MousePos );
		break;
	case MouseMove:
		ptrAction = MouseMoveAction( MousePos );
		break;
	case KeyDown:
		ptrAction = KeyDownAction( wParam );
		break;
	case CharInput:
		ptrAction = CharInputAction( wParam );
		break;
	default:
		ptrAction = NULL;
		break;
	}
	
	if (ptrAction)
		AddAction( ptrAction );
}
//--------------------------------------------------
void ActionModule::btnExit( void )
{
	// TODO: add codes for button exit action
	singActionModule::instance().AddAction( static_cast< ActionBase* >( new ActExit ) );
}
