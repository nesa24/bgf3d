#pragma once
#include "phase.h"

class TestPhase :
	public Phase
{
public:
	TestPhase(void);
	~TestPhase(void);

	//override
	static Phase* CreatePhase()
	{
		return new TestPhase;
	}

	bool Leave( void );
	bool Enter( void );
	void RealTimeLogic(void);
	void KeyDown( const WPARAM &wKey );
	void LogicKeyDown();


private:
	vector<void*> m_vec_pTestPrimitive;
};
