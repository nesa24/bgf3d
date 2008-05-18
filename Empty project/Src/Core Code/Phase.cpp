// Phase.cpp: Implement of the Phase class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Phase.h"
#include "CallHit.h"
#include <vector>
#include <algorithm>
using namespace std;

//////////////////////////////////////////////////////////////////////////
// Phase method Implement
//////////////////////////////////////////////////////////////////////////

class _FindPanel : public binary_function< Panel*, string, bool >
{
public:
	bool operator()( Panel* ptrPanel, string strName ) const
	{
		return (ptrPanel->GetName() == strName);
	}
};

string Phase::GetPhaseName()
{
	return m_Name;
}

bool Phase::Enter()
{
	return false;
}

bool Phase::Leave()
{
	return false;
}


bool Phase::AddPanel(Panel *ThisPanel)
{
	m_Panels.push_back( ThisPanel );
	return true;
}


bool Phase::SetName( std::string pName )
{
	//using namespace ConstStuff;
	if (!pName.empty())
		m_Name = pName;
	return false;
}

// Construction/Destruction
Phase::Phase()
{
	m_objFocus = NULL;
	m_panFocusedPanel = NULL;
}

Phase::~Phase()
{
//	m_Panels.clear();
}

Phase* Phase::CreatePhase()
{
	return new Phase;
}

void Phase::Draw(Canvas* pCanvas)
{
	vector<Panel*>::iterator itr;
	vector<Panel*>::iterator itr_end = m_Panels.end();
	for ( itr = m_Panels.begin(); itr != itr_end; ++itr )
	{
		(*itr)->Draw( pCanvas );
	}
}

void Phase::LogicKeyDown()
{
	vector<Panel*>::iterator itr;
	vector<Panel*>::iterator itr_end = m_Panels.end();
	for ( itr = m_Panels.begin(); itr != itr_end; ++itr )
	{
		(*itr)->LogicKeyDown();
	}
}

void Phase::CharInput( UINT nChar )
{
	vector<Panel*>::iterator itr;
	vector<Panel*>::iterator itr_end = m_Panels.end();
	for ( itr = m_Panels.begin(); itr != itr_end; ++itr )
	{
		(*itr)->CharInput( nChar );
	}
}

void Phase::RealTimeLogic(void)
{
	vector<Panel*>::iterator itr;
	vector<Panel*>::iterator itr_end = m_Panels.end();
	for ( itr = m_Panels.begin(); itr != itr_end; ++itr )
	{
		(*itr)->RealTimeLogic();
	}
}
//--------------------------------------------------
Panel* Phase::GetPanel( string strPanel )
{
	vector< Panel* >::iterator iter = 
		find_if( m_Panels.begin(), m_Panels.end(),
			bind2nd( _FindPanel(), strPanel ) );
	if (iter == m_Panels.end())
		return NULL;
	return *iter;
}
//--------------------------------------------------
template< typename T >
T* Phase::Parse( void )
{
	return static_cast< T* >( this );
}
//--------------------------------------------------
Panel* Phase::GetHitedPanel( const POINT &posMouse )
{
#ifdef USE_PANEL_RANGE
	typedef CallHit< Panel > PanelHitTest;
	// test all panels, and select high layer panel
	PanelHitTest result = for_each( m_Panels.begin(),
		m_Panels.end(), PanelHitTest( posMouse ) );
	
	if (!result.m_hitedObject)
		return NULL;
	else
		return result.m_hitedObject;
#else
	Object* objHited = NULL;
	Object* objTmp = NULL;
	vector< Panel* >::iterator iter = m_Panels.begin();
	vector< Panel* >::iterator iter_end = m_Panels.end();
	while (iter != iter_end)
	{
		objTmp = (*iter)->GetHitedItem( posMouse );
		if (!objHited)
			objHited = objTmp;
		if (objTmp->GetLayer() > objHited->GetLayer())
			objHited = objTmp;
	}
	return objHited;
#endif
}
//--------------------------------------------------
void Phase::MouseClickAt( const POINT &posMouse )
{
	CallHit< Panel > pObj = for_each( m_Panels.begin(), m_Panels.end(), 
		CallHit< Panel >( posMouse ) );
	if (pObj.m_hitedObject)
	{
		pObj.m_hitedObject->MouseClickAt( posMouse );

		//process the panel focus
		m_panFocusedPanel = (Panel*)pObj.m_hitedObject;
	}
}
//--------------------------------------------------
void Phase::KeyDown( const WPARAM &wKey )
{
	if( NULL == m_panFocusedPanel )
		return;
	
	m_panFocusedPanel->KeyDown( wKey );
}

//--------------------------------------------------
