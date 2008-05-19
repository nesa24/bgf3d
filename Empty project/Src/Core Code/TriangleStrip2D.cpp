#include "trianglestrip2D.h"

TriangleStrip2D::TriangleStrip2D(void)
{
	m_Color = 0xFFFFFFFF;

	m_iPrimitiveNbr = 0;
}


TriangleStrip2D::~TriangleStrip2D(void)
{
}


/////////////////////////////////////////////////////////////////
//method override
//different shape will have different method of creating vertex
void TriangleStrip2D::CreateVertexBuffer()
{
	g_pCanvas->GetGraphics()->CreateVertexBuffer( &m_pVertexBuffer, m_iPrimitiveNbr, true);
}
void TriangleStrip2D::UpdateVertexBuffer()
{
	if( m_iPrimitiveNbr <= 0 )
		return;

	//init vertex
	//Create vertex according to position and color
	vector<CustomVertex2D> vec_TempVertex;
	CustomVertex2D TempVertex;
	TempVertex.rhw  = 0.0f;
	TempVertex.z	= 0.0f;

	for( int i = 0; i < m_iPrimitiveNbr; ++i )
	{
		TempVertex.x = m_vec_PosList[i].x;
		TempVertex.y = m_vec_PosList[i].y;
		TempVertex.color = m_Color;

		vec_TempVertex.push_back( TempVertex );
	}

	//update vertex buffer
	g_pCanvas->GetGraphics()->UpdateVertexBuffer( &vec_TempVertex[0], m_pVertexBuffer, m_iPrimitiveNbr*sizeof(vec_TempVertex[0]) );
}

//Primitive type
ShapeType TriangleStrip2D::GetShapeType()
{
	return ShapeTriangleStrip;
}

//3D primitive type
bool TriangleStrip2D::Is3DShape()
{
	return false;
}


/////////////////////////////////////////////////////////////////
//unique method
void TriangleStrip2D::UpdatePos( POINT2D* pVertexes, const unsigned int iVertexNbr )
{
	//safty concern
	if( iVertexNbr <= 0 )
		return;

	//update vertex number
	if( m_iPrimitiveNbr != iVertexNbr )
	{
		m_iPrimitiveNbr = iVertexNbr;

		//recreate vertex buffer if there are change on number of vertex
		ReleaseVertexBuffer();
		CreateVertexBuffer();

		//rebuild the vector
		m_vec_PosList.clear();
		//update vertexes if it's the same number 
		for( int i = 0; i < m_iPrimitiveNbr; ++i )
		{
			m_vec_PosList.push_back( pVertexes[i] );
		}

	}
	else
	{
		//update vertexes if it's the same number 
		for( int i = 0; i < m_iPrimitiveNbr; ++i )
		{
			m_vec_PosList[i] = pVertexes[i];
		}
	}

	

	//update vertex buffer after alter of pos
	UpdateVertexBuffer();
}

void TriangleStrip2D::UpdateColor( const DWORD Color )
{
	m_Color = Color;

	//update vertex buffer after alter of color
	UpdateVertexBuffer();
}


