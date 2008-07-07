#include ".\line3d.h"

Line3D::Line3D(void)
{
	m_PosStart.x = 0;
	m_PosStart.y = 0;
	m_PosStart.z = 0;
	m_PosEnd.x = 0;
	m_PosEnd.y = 0;
	m_PosEnd.z = 0;

	m_iPrimitiveNbr = iVertexNumberLine2D;
}

Line3D::~Line3D(void)
{
}

/////////////////////////////////////////////////////////////////
//method override
//different shape will have different method of creating vertex
void Line3D::CreateVertexBuffer()
{
	g_pCanvas->GetGraphics()->CreateVertexBuffer( &m_pVertexBuffer, m_iPrimitiveNbr, false);
}

//the update of vertex is also different, accordingly
void Line3D::UpdateVertexBuffer()
{
	//init vertex
	//Create vertex according to position and color
	const DWORD Color = GetColorDWORD();
	CustomVertex3D TempVertex[2] = 
	{
		{ m_PosStart.x, m_PosStart.y, m_PosStart.z, Color },
		{ m_PosEnd.x,   m_PosEnd.y,   m_PosEnd.z,   Color },
	};

	//update vertex buffer
	g_pCanvas->GetGraphics()->UpdateVertexBuffer( TempVertex, m_pVertexBuffer, sizeof(TempVertex) );
}

//set rotating reference
void  Line3D::SetRot( int iAxisFlag, float fRotation )
{
	if( iAxisFlag < 3 && iAxisFlag >= 0 )
	{
		m_pfRot[iAxisFlag] = fRotation;
	}
}
//set Position reference
void  Line3D::SetPos( int iAxisFlag, float fPosition )
{
	if( iAxisFlag < 3 && iAxisFlag >= 0 )
	{
		m_pfPos[iAxisFlag] = fPosition;
	}
}

//Primitive type
ShapeType Line3D::GetShapeType()
{
	return ShapeLine;
}

//3D primitive type
bool Line3D::Is3DShape()
{
	return true;
}

/////////////////////////////////////////////////////////////////
//unique method
void Line3D::UpdatePos( const POINT3D PS, const POINT3D PE )
{
	m_PosStart = PS;
	m_PosEnd   = PE;

	//update vertex buffer after alter of pos
	UpdateVertexBuffer();
}

void Line3D::UpdateColor( const DWORD Color )
{
	SetColorDWORD( Color );

	//update vertex buffer after alter of color
	UpdateVertexBuffer();
}

