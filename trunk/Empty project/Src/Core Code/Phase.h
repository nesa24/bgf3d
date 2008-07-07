// Phase.h: interface for the Phase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PHASE_H__29355266_B208_4603_933F_656320850C4B__INCLUDED_)
#define AFX_PHASE_H__29355266_B208_4603_933F_656320850C4B__INCLUDED_


#include <windows.h>
#include "Enumerate.h"
#include "Panel.h"
#include "ConstStuff.h"
#include <vector>
#include <string>

using namespace std;

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*!
* \class Phase
* \brief The class of phase
*
* This class used to be the base Of all Phases
*/
class Phase  
{
public:
	//Construction
	Phase();
	virtual ~Phase();

	//Overridable basic phase funs
	virtual bool Leave();
	virtual bool Enter();

	//Overridable control method
	virtual void LogicKeyDown();
	virtual void CharInput( UINT nChar );
	virtual void KeyDown( const WPARAM &wKey );
	virtual void MouseClickAt( const POINT &posMouse );
	virtual void MouseMoveAt( const POINT &posMouse );
	//Overridable logic and present method
	virtual void Draw(Canvas* pCanvas);
	virtual void RealTimeLogic(void);

	//Not overridable basic phase funs
	string GetPhaseName();
	static Phase* CreatePhase();
	bool AddPanel( Panel* ThisPanel );
	bool ClearPanel( Panel* ThePanel );
	bool SetName( std::string pName );
	Panel* GetPanel( std::string strPanel );
	Panel* GetHitedPanel( const POINT &posMouse );
	inline void SetFocusObject( Object* obj )
	{
		m_objFocus = obj;
	}
	inline void ReleaseFocusObject(  )
	{
		if( NULL == m_objFocus )
			return;
		else
		{
			m_objFocus->LoseFocus();
			m_objFocus = NULL;

		}
	}
	inline Object* GetFocusObject( void )
	{
		return m_objFocus;
	}

	//unknown ones
	//most by Jmrol
	template< typename T > static T* Parse( void );



protected:
	vector<Panel*> m_Panels;
	string m_Name;
	Object* m_objFocus;
	Panel* m_panFocusedPanel;
};

#endif // !defined(AFX_PHASE_H__29355266_B208_4603_933F_656320850C4B__INCLUDED_)
