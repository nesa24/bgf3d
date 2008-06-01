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
	pLine->CreateVertexBuffer();
	pLine->UpdateColor( 0xFF000000 );
	pLine->UpdatePos( PS, PE );

	this->GetPanel( "panelDefault" )->AddObject( pObj );


	//triangle strip test
	int iside = 40;
	POINT2D posTri = {220, 10};
	pObj = singObjectFactory::instance().Create( "TriangleStrip2D" );
	TriangleStrip2D* pTriangleStrip = (TriangleStrip2D*)pObj;
	POINT2D Pos[4] = {
		{posTri.x, posTri.y},
		{posTri.x+iside, posTri.y},
		{posTri.x, posTri.y+iside},
		{posTri.x+iside, posTri.y+iside},
	};
	pTriangleStrip->CreateVertexBuffer();
	pTriangleStrip->UpdateColor( 0xFF000000 );
	pTriangleStrip->UpdatePos( Pos, 4 );

	this->GetPanel( "panelDefault" )->AddObject( pObj );


	//3D line test
	{
	pObj = singObjectFactory::instance().Create( "Line3D" );
	Line3D* pLine3D = (Line3D*)pObj;
	POINT3D PosLine3D[2] = {
		{-1.0f,0.0f,0.0f},
		{1.0f,1.0f,1.0f},
	};
	pLine3D->CreateVertexBuffer();
	pLine3D->UpdateColor( 0xFF000000 );
	pLine3D->UpdatePos( PosLine3D[0], PosLine3D[1] );

	this->GetPanel( "panelDefault" )->AddObject( pObj );
	}

	//3D line test
	{
	pObj = singObjectFactory::instance().Create( "Line3D" );
	Line3D* pLine3D = (Line3D*)pObj;
	POINT3D PosLine3D[2] = {
		{-1.0f,-1.0f,-1.0f},
		{1.0f,1.0f,1.0f},
	};
	pLine3D->CreateVertexBuffer();
	pLine3D->UpdateColor( 0xFF000000 );
	pLine3D->UpdatePos( PosLine3D[0], PosLine3D[1] );

	this->GetPanel( "panelDefault" )->AddObject( pObj );
	}

	//3D triangle test
	{
	pObj = singObjectFactory::instance().Create( "TriangleStrip3D" );
	TriangleStrip3D* pLine3D = (TriangleStrip3D*)pObj;
	POINT3D PosLine3D[4] = {
		{2.0f,-2.0f,0.0f},
		{-2.0f,-2.0f,0.0f},
		{2.0f,2.0f,0.0f},
		{-2.0f,2.0f,0.0f},
	};
	pLine3D->CreateVertexBuffer();
	pLine3D->UpdateColor( 0xAA666666 );
	pLine3D->UpdatePos(PosLine3D, 4);

	this->GetPanel( "panelDefault" )->AddObject( pObj );
	}
	//3D triangle test 2nd
	{
		pObj = singObjectFactory::instance().Create( "TriangleStrip3D" );
		TriangleStrip3D* pLine3D = (TriangleStrip3D*)pObj;
		POINT3D PosLine3D[4] = {
			{1.0f,-1.0f,0.0f},
			{-1.0f,-1.0f,0.0f},
			{1.0f,1.0f,0.0f},
			{-1.0f,1.0f,0.0f},
		};
		pLine3D->CreateVertexBuffer();
		pLine3D->UpdateColor( 0xFF000000 );
		pLine3D->UpdatePos(PosLine3D, 4);

		this->GetPanel( "panelDefault" )->AddObject( pObj );
	}
	return true;
}
