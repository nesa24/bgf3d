#pragma once
#include "shape.h"

class TriangleStrip3D :
	public Shape
{
public:
	TriangleStrip3D(void);
	~TriangleStrip3D(void);
public:
	//basic override
	static Object* CreateObject( void )
	{
		return (Object*)new TriangleStrip3D;
	}
	ObjectType GetObjectType( void ) const 
	{ 
		return ObjectPrimitveShape; 
	};


	//method override
	//different shape will have different method of creating vertex
	void CreateVertexBuffer();

	//the update of vertex is also different, accordingly
	void UpdateVertexBuffer();

	//For rotating 
	void  SetRot( int iAxisFlag, float fRotation );
	void  SetPos( int iAxisFlag, float fPosition );

	//type could be vary for different shapes 
	ShapeType GetShapeType();
	bool Is3DShape();

public:
	void UpdatePos( POINT3D* pVertexes, const unsigned int iVertexNbr );
	void UpdateColor( const DWORD Color );

private:
	vector<POINT3D> m_vec_PosList;
};
