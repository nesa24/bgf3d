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

	POINT PS = {0,0};
	POINT PE = {500,300};
	pLine->UpdateColor( 0xFF0000FF );
	pLine->UpdatePos( PS, PE );
	pLine->CreateVertexBuffer();

	this->GetPanel( "panelDefault" )->AddObject( pObj );

	//another line
	pObj = singObjectFactory::instance().Create( "Line2D" );
	pLine = (Line2D*)pObj;
	PS.x++;
	PE.x++;
	pLine->CreateVertexBuffer();
	pLine->UpdateColor( 0xFF0000FF );
	pLine->UpdatePos( PS, PE );

	this->GetPanel( "panelDefault" )->AddObject( pObj );

	//point test
	pObj = singObjectFactory::instance().Create( "Point2D" );
	Point2D* pPoint = (Point2D*)pObj;
	PS.x+= 10;
	PE.x+= 10;
	pPoint->CreateVertexBuffer();
	pPoint->UpdateColor( 0xFF00FF00 );
	pPoint->UpdatePos( PE );

	this->GetPanel( "panelDefault" )->AddObject( pObj );

	//triangle strip test
	pObj = singObjectFactory::instance().Create( "TriangleStrip2D" );
	TriangleStrip2D* pTriangleStrip = (TriangleStrip2D*)pObj;
	POINT Pos[3] = {
		{30, 40},
		{50, 40},
		{30, 80},
	};
	pTriangleStrip->CreateVertexBuffer();
	pTriangleStrip->UpdateColor( 0xFF0000FF );
	pTriangleStrip->UpdatePos( Pos, 3 );

	this->GetPanel( "panelDefault" )->AddObject( pObj );


	return true;
}
