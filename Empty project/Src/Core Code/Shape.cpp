#include ".\shape.h"

Shape::Shape(void)
{
	m_iPrimitiveNbr = 0;
	m_pVertexBuffer = NULL;

	m_pfRot[0] = 0;
	m_pfRot[1] = 0;
	m_pfRot[2] = 0;

	m_pfPos[0] = 0;
	m_pfPos[1] = 0;
	m_pfPos[2] = 0;
}

Shape::~Shape(void)
{
	ReleaseVertexBuffer();
}


//release vertex buffer
void Shape::ReleaseVertexBuffer()
{
	g_pCanvas->GetGraphics()->ReleaseVertexBuffer( m_pVertexBuffer );
}
