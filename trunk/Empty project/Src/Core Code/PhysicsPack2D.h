#pragma once
#include "expack.h"

//Type of physical fields
enum FieldType
{
	FieldSingleDrct,
	FieldConcentric,
	FieldSwirly,

	//number of fields
	FieldNbr,
};

//physical using vector
struct PhysicsVec2D
{
	float X;
	float Y;
};


class PhysicsPack2D :
	public Expack
{
public:
	PhysicsPack2D(void);
	virtual ~PhysicsPack2D(void);

	//pack create method
	static void* CreatePack(void)
	{
		return (void*)new PhysicsPack2D;
	};

	string GetPackName()
	{
		return "PhysicsPack2D";
	};


	//Basic physics data
private:
	//Basic data
	float m_fMass;
	float m_fFriction;
	PhysicsVec2D m_VecSpeed;
	PhysicsVec2D m_VecAcceleration;
	PhysicsVec2D m_PosMassPoint;		//the offset distance based on object's current painting position
										//basicly all the math of physics is based on the mass point not object's painting position

	//field data
	bool m_bFieldPhysicsDataEnable;
	//field space data
	float m_fFieldRadius;
	float m_fFieldRect[2];
	PhysicsVec2D m_VecFieldDrct;
	//field type and power
	FieldType	m_FieldType;
	bool m_bIsForceField;
	bool m_bIsGravityField;
	float m_fForcePower;
	float m_fGravityPower;

};
