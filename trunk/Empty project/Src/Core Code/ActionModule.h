/**
	Action generate class, singleton, to generate actions
 */

#ifndef BOK_ACTION_MODULE_H
#define BOK_ACTION_MODULE_H

#pragma warning( disable:4786 )

#include "ActionTypes.h"
#include "Enumerate.h"
#include <queue>
using namespace std;

// TODO:
//	add action generate codes here

class ActionModule
{
	typedef std::queue< ActionBase * > ActionQueue;
public:
	virtual ~ActionModule( void );

    void Generate( InputType input, WPARAM wParam, LPARAM lParam );

	// TODO:
	//		Add method for each type of actions, for generating.

	ActionBase* LClickAction( POINT pos );
	ActionBase* MouseMoveAction( POINT pos );
	ActionBase* KeyDownAction( WPARAM Key );
	ActionBase* CharInputAction( WPARAM Key );

	void AddAction( ActionBase* action )
	{
		m_actionQueue.push( action );
	}

	void Process( void );
	// TODO: add your own button-action
	static void btnExit( void );

protected:
	ActionModule( void );
	ActionQueue		m_actionQueue;
};

#endif
