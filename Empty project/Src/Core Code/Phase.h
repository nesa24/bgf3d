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
	//ly's Added
	virtual bool Leave();
	virtual bool Enter();
	virtual void RealTimeLogic(void);
	virtual void MouseClickAt( const POINT &posMouse );
	virtual void KeyDown( const WPARAM &wKey );
	string GetPhaseName();

	bool AddPanel( Panel* ThisPanel );
	bool ClearPanel( Panel* ThePanel );
	bool SetName( std::string pName );
	Panel* GetPanel( std::string strPanel );
	static Phase* CreatePhase();
	template< typename T > static T* Parse( void );
	Panel* GetHitedPanel( const POINT &posMouse );
	inline void SetFocusObject( Object* obj )
	{
		m_objFocus = obj;
	}
	inline Object* GetFocusObject( void )
	{
		return m_objFocus;
	}


	//Construction
	Phase();
	virtual ~Phase();

protected:
	vector<Panel*> m_Panels;
	string m_Name;
	Object* m_objFocus;
	Panel* m_panFocusedPanel;
public:
	//kyo's Added
	virtual void Draw(Canvas* pCanvas);
	virtual void LogicKeyDown();
	virtual void CharInput( UINT nChar );
};

#endif // !defined(AFX_PHASE_H__29355266_B208_4603_933F_656320850C4B__INCLUDED_)
