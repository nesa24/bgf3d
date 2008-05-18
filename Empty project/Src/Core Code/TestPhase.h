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

};
