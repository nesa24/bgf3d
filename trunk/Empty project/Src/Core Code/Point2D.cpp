#include ".\point2d.h"

Point2D::Point2D(void)
{
	m_Pos.x = 0;
	m_Pos.y = 0;
	m_Color = 0xFFFFFFFF;

	m_iPrimitiveNbr = iVertexNumberPoint2D;

	//set initial layer
	m_uiLayer = i2DPrimitiveInitLayer;
}

Point2D::~Point2D(void)
{
}


/////////////////////////////////////////////////////////////////
//method override
//different shape will have different method of creating vertex
void Point2D::CreateVertexBuffer()
{
	g_pCanvas->GetGraphics()->CreateVertexBuffer( &m_pVertexBuffer, m_iPrimitiveNbr, true);
}

//the update of vertex is also different, accordingly
void Point2D::UpdateVertexBuffer()
{
	//init vertex
	//Set the layer of the primitive as the layer of the object
	const float fLayer = this->GetLayer() / 10000.0f;

	//Create vertex according to position and color
	CustomVertex2D TempVertex[1] = {
		{ m_Pos.x, m_Pos.y, fLayer, 0.0f, m_Color },
	};

	//update vertex buffer
	g_pCanvas->GetGraphics()->UpdateVertexBuffer( TempVertex, m_pVertexBuffer, sizeof(TempVertex) );
}

//Primitive type
ShapeType Point2D::GetShapeType()
{
	return ShapePoint;
}

//3D primitive type
bool Point2D::Is3DShape()
{
	return false;
}

/////////////////////////////////////////////////////////////////
//unique method
void Point2D::UpdatePos( const POINT2D Pos )
{
	m_Pos = Pos;

	//update vertex buffer after alter of pos
	UpdateVertexBuffer();

}

void Point2D::UpdateColor( const DWORD Color )
{
	m_Color = Color;

	//update vertex buffer after alter of color
	UpdateVertexBuffer();
}
