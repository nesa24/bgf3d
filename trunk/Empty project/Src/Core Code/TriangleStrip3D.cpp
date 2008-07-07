#include ".\trianglestrip3d.h"

TriangleStrip3D::TriangleStrip3D(void)
{
	m_iPrimitiveNbr = 0;

}

TriangleStrip3D::~TriangleStrip3D(void)
{
}


/////////////////////////////////////////////////////////////////
//method override
//different shape will have different method of creating vertex
void TriangleStrip3D::CreateVertexBuffer()
{
	g_pCanvas->GetGraphics()->CreateVertexBuffer( &m_pVertexBuffer, m_iVertexNumber, false);
}
void TriangleStrip3D::UpdateVertexBuffer()
{
	if( m_iVertexNumber <= 0 )
		return;

	//init vertex
	//Create vertex according to position and color
	vector<CustomVertex3D> vec_TempVertex;
	CustomVertex3D TempVertex;

	for( int i = 0; i < m_iVertexNumber; ++i )
	{
		TempVertex.x = m_vec_PosList[i].x;
		TempVertex.y = m_vec_PosList[i].y;
		TempVertex.z = m_vec_PosList[i].z;

		TempVertex.color = GetColorDWORD();
		vec_TempVertex.push_back( TempVertex );
	}


	//update vertex buffer
	g_pCanvas->GetGraphics()->UpdateVertexBuffer( &vec_TempVertex[0], m_pVertexBuffer, m_iVertexNumber*sizeof(vec_TempVertex[0]) );
}



//set rotating reference
void  TriangleStrip3D::SetRot( int iAxisFlag, float fRotation )
{
	if( iAxisFlag < 3 && iAxisFlag >= 0 )
	{
		m_pfRot[iAxisFlag] = fRotation;
	}
}
//set Position reference
void  TriangleStrip3D::SetPos( int iAxisFlag, float fPosition )
{
	if( iAxisFlag < 3 && iAxisFlag >= 0 )
	{
		m_pfPos[iAxisFlag] = fPosition;
	}
}

//Primitive type
ShapeType TriangleStrip3D::GetShapeType()
{
	return ShapeTriangleStrip;
}

//3D primitive type
bool TriangleStrip3D::Is3DShape()
{
	return true;
}


/////////////////////////////////////////////////////////////////
//unique method
void TriangleStrip3D::UpdatePos( POINT3D* pVertexes, const unsigned int iVertexNbr )
{
	//safty concern
	if( iVertexNbr <= 0 )
		return;

	//update vertex number
	if( m_iVertexNumber != iVertexNbr )
	{
		m_iVertexNumber = iVertexNbr;
		//get primitive number according to vertex number
		m_iPrimitiveNbr = m_iVertexNumber - 2;

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
			m_vec_PosList[i] = pVertexes[i];
		}
	}

	

	//update vertex buffer after alter of pos
	UpdateVertexBuffer();
}

void TriangleStrip3D::UpdateColor( const DWORD Color )
{
	SetColorDWORD( Color );

	//update vertex buffer after alter of color
	UpdateVertexBuffer();
}