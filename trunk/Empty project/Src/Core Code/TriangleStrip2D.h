#pragma once
#include "shape.h"
#include <vector>

using namespace std;

class TriangleStrip2D :
	public Shape
{
public:
	TriangleStrip2D(void);
	~TriangleStrip2D(void);
public:
	//basic override
	static Object* CreateObject( void )
	{
		return (Object*)new TriangleStrip2D;
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
	void UpdatePos( POINT* pVertexes, const unsigned int iVertexNbr );
	void UpdateColor( const DWORD Color );

private:
	vector<POINT> m_vec_PosList;
	DWORD m_Color;
};
