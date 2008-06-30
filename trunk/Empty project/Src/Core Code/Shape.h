#pragma once
#include "object.h"
#include "../Graphics/GameGraphics.h"
#include "GlobalStuff.h"

const int iVertexNumberPoint2D = 1;
const int iVertexNumberLine2D = 2;
const int iVertexNumberTriangle2D = 3;
const int i2DPrimitiveInitLayer = 8500;

struct POINT2D
{
	float x,y;
	DWORD color;
};
struct POINT3D
{
	float x,y,z;
	DWORD color;
};


class Shape :
	public Object
{
public:
	Shape(void);
	~Shape(void);

public:
	//Override from object
	ObjectType GetObjectType( void ) const 
	{ 
		return ObjectPrimitveShape; 
	};


public:
	//virtual funs
	//different shape will have different method of creating vertex
	virtual void CreateVertexBuffer() = 0;

	//the update of vertex is also different, accordingly
	virtual void UpdateVertexBuffer() = 0;

	//For rotating 
	//return 0 if base method is invoked
	virtual void  SetRot( int iAxisFlag, float fRotation ) { return; };
	virtual void  SetPos( int iAxisFlag, float fPosition ) { return; };

	//type could be vary for different shapes 
	virtual ShapeType GetShapeType() = 0;
	virtual bool Is3DShape() = 0;

public:
	//basic functions
	//every vertex buffer will be stored in shape and accessed with a void pointer
	inline void* GetVertexBuffer() { return m_pVertexBuffer; };
	inline int   GetPrimitiveNbr() { return m_iPrimitiveNbr; };
	float* GetRotationSet() { return m_pfRot; };
	float* GetPosition() { return m_pfPos; };
	void ReleaseVertexBuffer();

protected:
	void* m_pVertexBuffer;
	int	  m_iPrimitiveNbr;
	float m_pfRot[3];		//rotation at most for 3 dimensions
	float m_pfPos[3];		//position at most for 3 dimensions
};
