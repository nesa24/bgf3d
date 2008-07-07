#pragma once

#include "PhysicsPack2D.h"

class PhysicsModule
{
public:
	PhysicsModule(void);
	~PhysicsModule(void);



	//General process interface functions
	void Do2DPhysicalMove();
	void Do3DPhysicalMove();

	//Detail process functions
	void UpDateAcceleration( bool Is3DPhysics );
	void CollisionTest( bool Is3DPhysics );
	void SetFinalSpeed( bool Is3DPhysics );
	void Move( bool Is3DPhysics );
};
