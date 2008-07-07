#pragma once
#include "shape.h"


class CombinedPrimitive3D :
	public Shape
{
public:
	CombinedPrimitive3D(void);
	~CombinedPrimitive3D(void);

//basic override
public:
	static Object* CreateObject( void )
	{
		return (Object*)new CombinedPrimitive3D;
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

	//setting  rotation and pos
	void  SetRot( int iAxisFlag, float fRotation );
	void  SetPos( int iAxisFlag, float fPosition );
	void  SetRot( float* pRotation );
	void  SetPos( float* pPosition );

	//Draw primitive
	bool Draw(Canvas* pCanvas);

//Unique methods
public:
	bool AddShape( Shape* pShape );

private:
	vector<Shape*> m_vecShapes;
};
