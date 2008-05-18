#pragma once
#include "shape.h"

class Line2D :
	public Shape
{
public:
	Line2D(void);
	~Line2D(void);

public:
	//basic override
	static Object* CreateObject( void )
	{
		return (Object*)new Line2D;
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
	void UpdatePos( const POINT PS, const POINT PE );
	void UpdateColor( const DWORD Color );

private:
	POINT m_PosStart;
	POINT m_PosEnd;
	DWORD m_Color;
};
