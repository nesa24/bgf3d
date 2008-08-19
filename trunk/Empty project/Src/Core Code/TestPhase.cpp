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
	Object* pObj;

	//3D Combine primitive test 
	{
		pObj = singObjectFactory::instance().Create( "CombinedPrimitive3D" );
		this->GetPanel( "panelDefault" )->AddObject( pObj );
		CombinedPrimitive3D* pCP = (CombinedPrimitive3D*)pObj;
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
		

	/*/3D triangle test 2nd
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
	//*/

	
	return true;
}


//RTL override
void TestPhase::RealTimeLogic(void)
{
	static float fRot = 0.0f;
	static float fPos = 0.0f;

	if( NULL != m_vec_pTestPrimitive[0] && NULL != m_vec_pTestPrimitive[1] )
	{
		fRot += 0.05f;
		fPos += 0.01f;
//		((Shape*)m_vec_pTestPrimitive[1])->SetRot( AxisY, fRot );
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

	/////////////////////////////
	//RTL basis
	vector<Panel*>::iterator itr;
	vector<Panel*>::iterator itr_end = m_Panels.end();
	for ( itr = m_Panels.begin(); itr != itr_end; ++itr )
	{
		(*itr)->RealTimeLogic();
	}
}

//Key control override
void TestPhase::KeyDown( const WPARAM &wKey )
{

}
void TestPhase::LogicKeyDown()
{
	Object* pObj = NULL;
	POINT PosLT = {100,100};
	Shape* pShapeLine = (Shape*)m_vec_pTestPrimitive[0];

	float* pLinePos = pShapeLine->GetPosition();
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
	if( GetAsyncKeyState('Q') )
		singCamera::instance().ZoomIn();
	if( GetAsyncKeyState('E') )
		singCamera::instance().ZoomOut();
	if( GetAsyncKeyState('C') )
		singCamera::instance().SetDefaultPosition();
	if( GetAsyncKeyState(VK_ESCAPE) )
		PostQuitMessage(0);
	if( GetAsyncKeyState('C') )
	{
		//square panel test
		PosLT.x = rand()%600;
		PosLT.y = rand()%800;
		pObj = singObjectFactory::instance().Create("SquarePanel");
		pObj->SetPosLT( PosLT );
		PosLT.x = rand()%200;
		PosLT.y = rand()%200;
		pObj->SetSize( PosLT );

		AddPanel( (Panel*)pObj );
	}

	pShapeLine->SetPos( pLinePos );

	//Do the rest
	vector<Panel*>::iterator itr;
	vector<Panel*>::iterator itr_end = m_Panels.end();
	for ( itr = m_Panels.begin(); itr != itr_end; ++itr )
	{
		(*itr)->LogicKeyDown();
	}
}
