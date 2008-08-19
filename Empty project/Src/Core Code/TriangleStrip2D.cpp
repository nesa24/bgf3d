#include "trianglestrip2D.h"

TriangleStrip2D::TriangleStrip2D(void)
{
	m_iPrimitiveNbr = 0;

	//set initial layer
	m_uiLayer = i2DPrimitiveInitLayer;
}


TriangleStrip2D::~TriangleStrip2D(void)
{
}



/////////////////////////////////////////////////////////////////
//method override
//different shape will have different method of creating vertex
void TriangleStrip2D::CreateVertexBuffer()
{
	g_pCanvas->GetGraphics()->CreateVertexBuffer( &m_pVertexBuffer, m_iVertexNumber, true);
}
void TriangleStrip2D::UpdateVertexBuffer()
{
	if( m_iVertexNumber <= 0 )
		return;

	//init vertex
	//Set the layer of the primitive as the layer of the object
	const float fLayer = this->GetLayer() / 10000.0f;

	//Create vertex according to position and color
	vector<CustomVertex2D> vec_TempVertex;
	CustomVertex2D TempVertex;
	TempVertex.rhw  = 0.0f;
	TempVertex.z	= fLayer;

	for( int i = 0; i < m_iVertexNumber; ++i )
	{
		TempVertex.x = m_vec_PosList[i].x;
		TempVertex.y = m_vec_PosList[i].y;
		TempVertex.color = m_vec_PosList[i].color;

		vec_TempVertex.push_back( TempVertex );
	}

	//update vertex buffer
	g_pCanvas->GetGraphics()->UpdateVertexBuffer( &vec_TempVertex[0], m_pVertexBuffer, m_iVertexNumber*sizeof(vec_TempVertex[0]) );
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
void TriangleStrip2D::UpdatePos( POINT2D* pVertexes, const unsigned int iVertexNbr, const bool bUpdateColor )
{
	//safty concern
	if( iVertexNbr <= 0 )
		return;

	//update vertex number
	if( m_iVertexNumber != iVertexNbr )
	{
		m_iVertexNumber = iVertexNbr;
		//get primitive number according to vertex number
		m_iPrimitiveNbr = m_iVertexNumber-2;

		//recreate vertex buffer if there are change on number of vertex
		ReleaseVertexBuffer();
		CreateVertexBuffer();

		//rebuild the vector
		m_vec_PosList.clear();
		//remake vertexes if it is not the same number 
		for( int i = 0; i < m_iVertexNumber; ++i )
		{
			m_vec_PosList.push_back( pVertexes[i] );
		}

	}
	else
	{
		//update vertexes if it's the same number 
		for( int i = 0; i < m_iVertexNumber; ++i )
		{
			m_vec_PosList[i].x = pVertexes[i].x;
			m_vec_PosList[i].y = pVertexes[i].y;
			if( bUpdateColor )
				m_vec_PosList[i].color = pVertexes[i].color;
		}
	}

	

	//update vertex buffer after alter of pos
	UpdateVertexBuffer();
}

void TriangleStrip2D::UpdateColor( const DWORD Color )
{
	SetColorDWORD( Color );
	for( int i = 0; i < m_iVertexNumber; ++i )
	{
		m_vec_PosList[i].color = GetColorDWORD();
	}

	//update vertex buffer after alter of color
	UpdateVertexBuffer();
}


