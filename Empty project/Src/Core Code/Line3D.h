#pragma once
#include "shape.h"

class Line3D :
	public Shape
{
public:
	Line3D(void);
	~Line3D(void);

public:
	//basic override
	static Object* CreateObject( void )
	{
		return (Object*)new Line3D;
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
	void UpdatePos( const POINT3D PS, const POINT3D PE );
	void UpdateColor( const DWORD Color );

private:
	POINT3D m_PosStart;
	POINT3D m_PosEnd;
};
