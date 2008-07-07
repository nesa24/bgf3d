#include "testphase.h"
#include "stdafx.h"

TestPhase::TestPhase(void)
{
//	m_pTestPrimitive = NULL;
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
	pLine->UpdateColor( 0xFFAA0000 );
	pLine->UpdatePos( PS, PE );
	pLine->GetExPack()->AddPack( (Expack*)singFactory::instance().Create("Expack_Physics2D") );
	pLine->GetExPack()->AddPack( (Expack*)singFactory::instance().Create("Expack_Physics2D") );

	if( !pLine->GetExPack()->FindPack( "PhysicsPack2D" ) )
		this->GetPanel( "panelDefault" )->AddObject( pObj );


	//*triangle strip test
	int iside = 30;
	POINT2D posTri = {320, 10};
	pObj = singObjectFactory::instance().Create( "TriangleStrip2D" );
	TriangleStrip2D* pTriangleStrip = (TriangleStrip2D*)pObj;
	POINT2D Pos[4] = {
		{posTri.x, posTri.y},
		{posTri.x+iside, posTri.y},
		{posTri.x, posTri.y+iside},
		{posTri.x+iside, posTri.y+iside},
	};
	pTriangleStrip->CreateVertexBuffer();
	pTriangleStrip->UpdateColor( 0xFFAAAAAA );
	pTriangleStrip->UpdatePos( Pos, 4 );
	POINT tempPos = {1,1};
	POINT tempPos2 = {400,400};
	pTriangleStrip->SetPosLT(tempPos);
	pTriangleStrip->SetSize(tempPos2);

	this->GetPanel( "panelDefault" )->AddObject( pObj );
	//*/

	//3D line test
	{
	pObj = singObjectFactory::instance().Create( "Line3D" );
	Line3D* pLine3D = (Line3D*)pObj;
	POINT3D PosLine3D[2] = {
		{1.0f,1.0f,1.0f},
		{0.0f,0.0f,0.0f},
	};
	pLine3D->CreateVertexBuffer();
	pLine3D->UpdateColor( 0xFFFF00FF );
	pLine3D->UpdatePos( PosLine3D[0], PosLine3D[1] );

	this->GetPanel( "panelDefault" )->AddObject( pObj );
	m_vec_pTestPrimitive.push_back( (void*)pObj );
	}

	/*/3D triangle test
	{
	pObj = singObjectFactory::instance().Create( "TriangleStrip3D" );
	TriangleStrip3D* pLine3D = (TriangleStrip3D*)pObj;
	POINT3D PosLine3D[4] = {
		{2.0f,2.0f,-0.3f},
		{-2.0f,2.0f,-0.3f},
		{2.0f,-2.0f,-0.3f},
		{-2.0f,-2.0f,-0.3f},
	};
	pLine3D->CreateVertexBuffer();
	pLine3D->UpdateColor( 0xAA00000F );
	pLine3D->UpdatePos(PosLine3D, 4);

	this->GetPanel( "panelDefault" )->AddObject( pObj );
	}
	*/


	//3D Combine primitive test 
	{
		pObj = singObjectFactory::instance().Create( "CombinedPrimitive3D" );
		CombinedPrimitive3D* pCP = (CombinedPrimitive3D*)pObj;
		this->GetPanel( "panelDefault" )->AddObject( pObj );
		m_vec_pTestPrimitive.push_back( (void*)pObj );



		pObj = singObjectFactory::instance().Create( "TriangleStrip3D" );
		TriangleStrip3D* pLine3D = (TriangleStrip3D*)pObj;
		POINT3D PosLine3D[10] = {
			{-1.0f,1.0f,-1.0f},
			{-1.0f,-1.0f,-1.0f},
			{1.0f,1.0f,-1.0f},
			{1.0f,-1.0f,-1.0f},
			{1.0f,1.0f,1.0f},
			{1.0f,-1.0f,1.0f},
			{-1.0f,1.0f,1.0f},
			{-1.0f,-1.0f,1.0f},
			{-1.0f,1.0f,-1.0f},
			{-1.0f,-1.0f,-1.0f},
		};
		pLine3D->CreateVertexBuffer();
		pLine3D->UpdateColor( 0xFF111111 );
		pLine3D->UpdatePos(PosLine3D, 10);
		pCP->AddShape( (Shape*)pLine3D );

		pObj = singObjectFactory::instance().Create( "TriangleStrip3D" );
		pLine3D = (TriangleStrip3D*)pObj;
		POINT3D PosLine3D_2[4] = {
			{1.0f,1.0f,-1.0f},
			{1.0f,1.0f,1.0f},
			{3.0f,1.0f,-1.0f},
			{3.0f,1.0f,1.0f},
		};
		pLine3D->CreateVertexBuffer();
		pLine3D->UpdateColor( 0xFFAA1111 );
		pLine3D->UpdatePos(PosLine3D_2, 4);
		pCP->AddShape( (Shape*)pLine3D );

		pObj = singObjectFactory::instance().Create( "TriangleStrip3D" );
		pLine3D = (TriangleStrip3D*)pObj;
		POINT3D PosLine3D_3[4] = {
			{-1.0f,-1.0f,-1.0f},
			{-1.0f,-1.0f,1.0f},
			{1.0f,-1.0f,-1.0f},
			{1.0f,-1.0f,1.0f},
		};
		pLine3D->CreateVertexBuffer();
		pLine3D->UpdateColor( 0xFF1111AA );
		pLine3D->UpdatePos(PosLine3D_3, 4);
		pCP->AddShape( (Shape*)pLine3D );


	}

	//3D triangle test 2nd
	{
		pObj = singObjectFactory::instance().Create( "TriangleStrip3D" );
		TriangleStrip3D* pLine3D = (TriangleStrip3D*)pObj;
		POINT3D PosLine3D[6] = {
			{2.0f,2.0f,-0.3f},
			{-2.0f,2.0f,-0.3f},
			{2.0f,-2.0f,-0.3f},
			{-2.0f,2.0f,-0.3f},
			{2.0f,-2.0f,-0.3f},
			{-2.0f,-2.0f,-0.3f},
		};
		pLine3D->CreateVertexBuffer();
		pLine3D->UpdateColor( 0x87654321 );
		pLine3D->UpdatePos(PosLine3D, 6);

		this->GetPanel( "panelDefault" )->AddObject( pObj );
		m_vec_pTestPrimitive.push_back( (void*)pObj );

	}
	

	return true;
}


//RTL override
void TestPhase::RealTimeLogic(void)
{
	static float fRot = 0.0f;
	static float fPos = 0.0f;

	if( NULL != m_vec_pTestPrimitive[0] )
	{
		fRot += 0.05f;
		fPos += 0.01f;
		((Shape*)m_vec_pTestPrimitive[1])->SetRot( AxisY, fRot );
//		((Shape*)m_vec_pTestPrimitive[0])->SetPos( AxisY, fPos );
	}

	static float fMove = 0.0f;
	static bool Drct = true;
	if( 0.5f < fMove || fMove < -0.5f )
		Drct = !Drct;
	if( true == Drct )
		fMove += 0.01f;
	else
		fMove -= 0.01f;

	POINT3D Pos3D[4] = {
	{2.0f,-2.0f,-0.3f + fMove},
	{-2.0f,-2.0f,-0.3f + fMove},
	{2.0f,2.0f,-0.3f + fMove},
	{-2.0f,2.0f,-0.3f + fMove},
	};

	if( NULL != m_vec_pTestPrimitive[1] )
	{
		//((TriangleStrip3D*)m_vec_pTestPrimitive[1])->UpdatePos(Pos3D, 4);
		//((TriangleStrip3D*)m_vec_pTestPrimitive[1])->SetRot( 1, fRot );
	}
}

//Key control override
void TestPhase::KeyDown( const WPARAM &wKey )
{

}
void TestPhase::LogicKeyDown()
{
	Shape* pShapeLine = (Shape*)m_vec_pTestPrimitive[1];
	Shape* pShapeBG = (Shape*)m_vec_pTestPrimitive[2];

	float* pLinePos = pShapeLine->GetPosition();
	float* pBGPos = pShapeBG->GetPosition();
	const float fStep = 0.04;

	if( GetAsyncKeyState('W') )
		pLinePos[AxisZ] += fStep;

	if( GetAsyncKeyState('S') )
		pLinePos[AxisZ] -= fStep;

	if( GetAsyncKeyState('A') )
		pLinePos[AxisX] -= fStep;
	if( GetAsyncKeyState('D') )
		pLinePos[AxisX] += fStep;
	if( GetAsyncKeyState(VK_SPACE) )
		pLinePos[AxisY] += fStep;
	if( GetAsyncKeyState('R') )
		pLinePos[AxisY] -= fStep;
	if( GetAsyncKeyState('X') )
		pBGPos[AxisZ] += fStep;
	if( GetAsyncKeyState('Z') )
		pBGPos[AxisZ] -= fStep;
	if( GetAsyncKeyState('Q') )
		singCamera::instance().ZoomIn();
	if( GetAsyncKeyState('E') )
		singCamera::instance().ZoomOut();
	if( GetAsyncKeyState('C') )
		singCamera::instance().SetDefaultPosition();

	pShapeLine->SetPos( pLinePos );

	//Do the rest
	vector<Panel*>::iterator itr;
	vector<Panel*>::iterator itr_end = m_Panels.end();
	for ( itr = m_Panels.begin(); itr != itr_end; ++itr )
	{
		(*itr)->LogicKeyDown();
	}
}
