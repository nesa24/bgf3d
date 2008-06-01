#include ".\line2d.h"

Line2D::Line2D(void)
{
	m_PosStart.x = 0;
	m_PosStart.y = 0;
	m_PosEnd.x = 0;
	m_PosEnd.y = 0;
	m_Color = 0xFFFFFFFF;

	m_iPrimitiveNbr = iVertexNumberLine2D;

	//set initial layer
	m_uiLayer = i2DPrimitiveInitLayer;
}

Line2D::~Line2D(void)
{
}

/////////////////////////////////////////////////////////////////
//method override
//different shape will have different method of creating vertex
void Line2D::CreateVertexBuffer()
{
	g_pCanvas->GetGraphics()->CreateVertexBuffer( &m_pVertexBuffer, m_iPrimitiveNbr, true);
}

//the update of vertex is also different, accordingly
void Line2D::UpdateVertexBuffer()
{
	//init vertex
	//Set the layer of the primitive as the layer of the object
	const float fLayer = this->GetLayer() / 10000.0f;

	//Create vertex according to position and color
	CustomVertex2D TempVertex[2] = {
		{ m_PosStart.x, m_PosStart.y, fLayer, 0.0f, m_Color },
		{ m_PosEnd.x,   m_PosEnd.y,   fLayer, 0.0f, m_Color },
	};

	//update vertex buffer
	g_pCanvas->GetGraphics()->UpdateVertexBuffer( TempVertex, m_pVertexBuffer, sizeof(TempVertex) );
}

//Primitive type
ShapeType Line2D::GetShapeType()
{
	return ShapeLine;
}

//3D primitive type
bool Line2D::Is3DShape()
{
	return false;
}

/////////////////////////////////////////////////////////////////
//unique method
void Line2D::UpdatePos( const POINT2D PS, const POINT2D PE )
{
	m_PosStart = PS;
	m_PosEnd   = PE;

	//update vertex buffer after alter of pos
	UpdateVertexBuffer();
}

void Line2D::UpdateColor( const DWORD Color )
{
	m_Color = Color;

	//update vertex buffer after alter of color
	UpdateVertexBuffer();
}

