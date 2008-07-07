#pragma once
#include "shape.h"

class Point2D :
	public Shape
{
public:
	Point2D(void);
	~Point2D(void);
public:
	//basic override
	static Object* CreateObject( void )
	{
		return (Object*)new Point2D;
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

	//type could be vary for different shapes 
	ShapeType GetShapeType();
	bool Is3DShape();

public:
	void UpdatePos( const POINT2D Pos );
	void UpdateColor( const DWORD Color );

private:
	POINT2D m_Pos;
};
