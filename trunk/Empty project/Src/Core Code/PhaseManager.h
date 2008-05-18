/*!
* CopyRight \b (c) 2006 BOKteam
* All Rights Reserved
*
* \file PhaseManager.h
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
#if !defined(AFX_PHASEMANAGER_H__09B9AF0A_5387_40D3_B458_1B8F63C13A5D__INCLUDED_)
#define AFX_PHASEMANAGER_H__09B9AF0A_5387_40D3_B458_1B8F63C13A5D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include "Phase.h"

using namespace std;

/*!
* \class PhaseManager
* \brief This class is a singleton!
*
* This class is a singleton!
* remember call the instance in this way
* [Code]
* PhaseManager & PM = PhaseManager::Instance();
* [/Code]
*/
class PhaseManager
{
public:
	inline Phase* GetCurrentPhase( void )
	{
		return m_CurrentPhase;
	}
	bool ChangeToPhase(const char* ThePhase );
	Phase* CreatePhase(const char* pName );
	Phase* GetThePhase(string strPhaseName );
	void AddPhase( Phase* ptrPhase );
	virtual ~PhaseManager();

protected:
	PhaseManager();
	vector< Phase* > m_AllPhases;
	Phase* m_CurrentPhase;
};

#endif // !defined(AFX_PHASEMANAGER_H__09B9AF0A_5387_40D3_B458_1B8F63C13A5D__INCLUDED_)
