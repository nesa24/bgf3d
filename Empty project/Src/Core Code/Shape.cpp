#include ".\shape.h"

Shape::Shape(void)
{
	m_iPrimitiveNbr = 0;
	m_pVertexBuffer = NULL;
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
