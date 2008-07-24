#include "StdAfx.h"
#include "PhaseManager.h"
#include "PhaseFactory.h"
#include <algorithm>

//--------------------------------------------------
PhaseManager::PhaseManager( void )
{
	m_CurrentPhase = NULL;
	m_AllPhases.clear();
}
//--------------------------------------------------
PhaseManager::~PhaseManager( void )
{
	// phase factory create all phases, with new operator
	// and phase manager take charge of deleting them
	vector< Phase* >::iterator iter = m_AllPhases.begin();
	vector< Phase* >::iterator iter_end = m_AllPhases.end();

	while( iter != iter_end )
	{
		SAFE_DELETE( *iter );
		++iter;
	}
	m_AllPhases.clear();
}
//--------------------------------------------------
bool PhaseManager::ChangeToPhase( const char* strPhase )
{
	Phase* pPhaseToGo = GetThePhase( strPhase );
	if( NULL == pPhaseToGo || m_CurrentPhase == pPhaseToGo )
		return false;

	bool _return = false;
	if (m_CurrentPhase->Leave())
	{
		m_CurrentPhase = pPhaseToGo;

		_return = m_CurrentPhase->Enter();
	}
	return _return;
}
//--------------------------------------------------
Phase* PhaseManager::CreatePhase( const char* pName )
{
	Phase* _return = NULL;	// NRV optimize.
	_return = singPhaseFactory::instance().Create( pName );

	m_AllPhases.push_back( _return );
	if (!m_CurrentPhase)
	{
		m_CurrentPhase = _return;
	}
	return _return;
}
//--------------------------------------------------
Phase* PhaseManager::GetThePhase( string strPhaseName )
{
	Phase* _return = NULL;
	vector< Phase* >::iterator iter = m_AllPhases.begin();
	vector< Phase* >::iterator iter_end = m_AllPhases.end();

	while( iter != iter_end )
	{
		_return = *iter;
		if (strPhaseName == _return->GetPhaseName())
		{
			_return = *iter;
			break;
		}
		++iter;
	}
	return _return;
}
//--------------------------------------------------
void PhaseManager::AddPhase( Phase* ptrPhase )
{
	m_AllPhases.push_back( ptrPhase );
	if (!m_CurrentPhase)
	{
		m_CurrentPhase = ptrPhase;
	}
}
