#include "testphase.h"
#include "stdafx.h"

TestPhase::TestPhase(void)
{
}

TestPhase::~TestPhase(void)
{
}


bool TestPhase::Leave( void )
{
	return true;
}
bool TestPhase::Enter( void )
{
	//test 2D line
	Object* pObj = singObjectFactory::instance().Create( "Line2D" );
	Line2D* pLine = (Line2D*)pObj;

	POINT2D PS = {0,0};
	POINT2D PE = {500,300};
	pLine->UpdateColor( 0xFF000000 );
	pLine->UpdatePos( PS, PE );
	pLine->CreateVertexBuffer();

	this->GetPanel( "panelDefault" )->AddObject( pObj );

	//another line
	pObj = singObjectFactory::instance().Create( "Line2D" );
	pLine = (Line2D*)pObj;
	PS.x++;
	PE.x++;
	pLine->CreateVertexBuffer();
	pLine->UpdateColor( 0xFF000000 );
	pLine->UpdatePos( PS, PE );

	this->GetPanel( "panelDefault" )->AddObject( pObj );

	//point test
	pObj = singObjectFactory::instance().Create( "Point2D" );
	Point2D* pPoint = (Point2D*)pObj;
	PS.x+= 10;
	PE.x+= 10;
	pPoint->CreateVertexBuffer();
	pPoint->UpdateColor( 0xFF000000 );
	pPoint->UpdatePos( PE );

	this->GetPanel( "panelDefault" )->AddObject( pObj );

	//triangle strip test
	pObj = singObjectFactory::instance().Create( "TriangleStrip2D" );
	TriangleStrip2D* pTriangleStrip = (TriangleStrip2D*)pObj;
	POINT2D Pos[3] = {
		{30, 40},
		{50, 40},
		{30, 80},
	};
	pTriangleStrip->CreateVertexBuffer();
	pTriangleStrip->UpdateColor( 0xFF000000 );
	pTriangleStrip->UpdatePos( Pos, 3 );

	this->GetPanel( "panelDefault" )->AddObject( pObj );

	//3D line test
	{
	pObj = singObjectFactory::instance().Create( "Line3D" );
	Line3D* pLine3D = (Line3D*)pObj;
	POINT3D PosLine3D[2] = {
		{1.0f,0.0f,0.0f},
		{1.0f,1.0f,-0.0f},
	};
	pLine3D->CreateVertexBuffer();
	pLine3D->UpdateColor( 0xFFFF0000 );
	pLine3D->UpdatePos( PosLine3D[0], PosLine3D[1] );

	this->GetPanel( "panelDefault" )->AddObject( pObj );
	}

	//3D line test
	{
	pObj = singObjectFactory::instance().Create( "Line3D" );
	Line3D* pLine3D = (Line3D*)pObj;
	POINT3D PosLine3D[2] = {
		{-1.0f,-1.0f,-00.0f},
		{1.0f,1.0f,0.0f},
	};
	pLine3D->CreateVertexBuffer();
	pLine3D->UpdateColor( 0xFFFF0000 );
	pLine3D->UpdatePos( PosLine3D[0], PosLine3D[1] );

	this->GetPanel( "panelDefault" )->AddObject( pObj );
	}

	return true;
}
