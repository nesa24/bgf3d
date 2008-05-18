// Canvas.cpp: Implement of the Canvas class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Canvas.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Canvas::Canvas()
{
	m_bFocus = true;
	m_bDirty = true;
	m_vctPicRes.clear();	
}

Canvas::~Canvas()
{
}

void Canvas::Render()
{
	if ( !m_bFocus )
		return;

	if ( m_bDirty )
	{
		m_pGameGraphics->FillSurface( 0, 0x0000ff );
		m_pGameGraphics->SetupMatrices();
		m_pGameGraphics->BeginRender();

		//render objects

		singPhaseManager::instance().GetCurrentPhase()->Draw( this );
		//render end
		
		m_pGameGraphics->EndRender();

	}

	m_pGameGraphics->Render();
}

BOOL Canvas::InitCanvas()
{
	m_pGameGraphics->InitGeometry();

	//load pictures
	int prsize = (int)m_vctPicRes.size();
	for ( int i = 0; i < prsize; ++i )
	{
		//create surface
		m_pGameGraphics->CreateSurface( 0, 0 );	
		m_pGameGraphics->LoadPic( i, ((char*)m_vctPicRes[i].c_str()) );	
	}

	//create font
	int ftsize = (int)m_vctFontType.size();
	for ( i = 0; i < ftsize; ++i )
	{
		m_pGameGraphics->DXCreateFont( m_vctFontSize[i], (char*)m_vctFontType[i].c_str(),
										m_vctFontThick[i], m_vctFontTrend[i] );
	}

	//add animation
	m_pHeadComponent = &(singDrawBasic::instance());

	m_pHeadComponent = m_pHeadComponent->AddComponent( &(singAnimationMoveX::instance()) );
	m_pHeadComponent = m_pHeadComponent->AddComponent( &(singAnimationMoveY::instance()) );
	m_pHeadComponent = m_pHeadComponent->AddComponent( &(singAnimationAlpha::instance()) );
	m_pHeadComponent = m_pHeadComponent->AddComponent( &(singAnimationCircumrotate::instance()) );
	m_pHeadComponent = m_pHeadComponent->AddComponent( &(singAnimationScale::instance()) );
	m_pHeadComponent = m_pHeadComponent->AddComponent( &(singAnimationFrame::instance()) );
	
	return TRUE;
}

void Canvas::ShutCanvas()
{
	m_pGameGraphics->ShutGraphics();
}

BOOL Canvas::CreateCanvas()
{
	m_pGameGraphics = CreateGameGraphics( hwndMain, TRUE, g_iWindow_Width, g_iWindow_Height );

	return TRUE;
}

void Canvas::RenderLoad()
{
}

CGameGraphics* Canvas::GetGraphics() const
{
	return m_pGameGraphics;
}

void Canvas::DrawRect( RECT &rect, float layer, int size, DWORD color )
{
}

int Canvas::DrawObject( Object* pObj )
{
	//对象为空不用渲染
	if ( NULL == pObj )
		return 1;

	if ( pObj->GetVisible() )
		m_pHeadComponent->Draw( pObj, this );

	return 0;
}
