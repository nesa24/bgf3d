#include ".\combinedprimitive3d.h"
#include "stdafx.h"


CombinedPrimitive3D::CombinedPrimitive3D(void)
{
}

CombinedPrimitive3D::~CombinedPrimitive3D(void)
{
	vector<Shape*>::iterator itr_each = m_vecShapes.begin();
	vector<Shape*>::iterator itr_end  = m_vecShapes.end();

	for( ;itr_each != itr_end; )
	{
		SAFE_DELETE( (*itr_each) );
		itr_each = m_vecShapes.erase( itr_each );
	}
}

/////////////////////////////////////////////////////////////////
//method override
//different shape will have different method of creating vertex
void CombinedPrimitive3D::CreateVertexBuffer()
{
}

//the update of vertex is also different, accordingly
void CombinedPrimitive3D::UpdateVertexBuffer()
{
}

//Primitive type
ShapeType CombinedPrimitive3D::GetShapeType()
{
	return ShapeVoid;
}

//3D primitive type
bool CombinedPrimitive3D::Is3DShape()
{
	return true;
}

//set rotating reference
void  CombinedPrimitive3D::SetRot( int iAxisFlag, float fRotation )
{
	if( iAxisFlag < 3 && iAxisFlag >= 0 )
	{
		m_pfRot[iAxisFlag] = fRotation;
	}

	//apply to all other primitives
	vector<Shape*>::iterator itr_each = m_vecShapes.begin();
	vector<Shape*>::iterator itr_end  = m_vecShapes.end();

	for( ;itr_each != itr_end; ++itr_each )
	{
		if( NULL != *itr_each )
			(*itr_each)->SetRot( &m_pfRot[0] );
	}
}
void  CombinedPrimitive3D::SetRot( float* pRotation ) 
{ 
	memcpy( (void*)m_pfRot, (void*)pRotation, sizeof(m_pfRot) ); 

	//apply to all other primitives
	vector<Shape*>::iterator itr_each = m_vecShapes.begin();
	vector<Shape*>::iterator itr_end  = m_vecShapes.end();

	for( ;itr_each != itr_end; ++itr_each )
	{
		if( NULL != *itr_each )
			(*itr_each)->SetRot( &m_pfRot[0] );
	}
};

//set Position reference
void  CombinedPrimitive3D::SetPos( int iAxisFlag, float fPosition )
{
	if( iAxisFlag < 3 && iAxisFlag >= 0 )
	{
		m_pfPos[iAxisFlag] = fPosition;
	}

	//apply to all other primitives
	vector<Shape*>::iterator itr_each = m_vecShapes.begin();
	vector<Shape*>::iterator itr_end  = m_vecShapes.end();

	for( ;itr_each != itr_end; ++itr_each )
	{
		if( NULL != *itr_each )
			(*itr_each)->SetPos( &m_pfPos[0] );
	}
}
void  CombinedPrimitive3D::SetPos( float* pPosition )
{ 
	memcpy( (void*)m_pfPos, (void*)pPosition, sizeof(m_pfPos) ); 

	//apply to all other primitives
	vector<Shape*>::iterator itr_each = m_vecShapes.begin();
	vector<Shape*>::iterator itr_end  = m_vecShapes.end();

	for( ;itr_each != itr_end; ++itr_each )
	{
		if( NULL != *itr_each )
			(*itr_each)->SetPos( &m_pfPos[0] );
	}
};

//draw method
bool CombinedPrimitive3D::Draw(Canvas* pCanvas)
{
	vector<Shape*>::iterator itr_each = m_vecShapes.begin();
	vector<Shape*>::iterator itr_end  = m_vecShapes.end();

	for( ;itr_each != itr_end; ++itr_each )
	{
		if( NULL != *itr_each )
			(*itr_each)->Draw( pCanvas );
	}
	return true;
}


/////////////////////////////////////////////////////////////////
//unique method
	
bool CombinedPrimitive3D::AddShape( Shape* pShape )
{
	if( NULL == pShape )
		return false;

	m_vecShapes.push_back( pShape );

	return true;
}

