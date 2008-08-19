#include "squarepanel.h"
#include "stdafx.h"

using namespace ns_SquarePanel;
const unsigned int iPanelOpenFrames = 8;
const unsigned int iPanelWaitFrames = 6;

SquarePanel::SquarePanel(void)
{
	//basic settings
	m_MyState = PanelInvisible;
	m_sOpeningPercent = 0;
	m_sClosingPercent = 0;
	m_PosVisualSize.x = 0;
	m_PosVisualSize.y = 0;
	m_bPanelLocked = true;

	//Create panel bottom rect
	Object* pObj = singObjectFactory::instance().Create( "TriangleStrip2D" );
	pObj->SetLayer( 1000 );
	AddObject( pObj );

	m_IDPanelBottom = singObjectLinker::instance().GetRegID( pObj );

	//set default setting
	SetPosLT( SquarePanelDefaultPos );
	SetSize( SquarePanelDefaultSize );
	PanelObjectPosUpdate();
	SetPanelColour( 0xFFFFFFFF, 0x7700CCFF );

	//Panel start with opening
	OpenPanel();
}

SquarePanel::~SquarePanel(void)
{
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Override from Panel
void SquarePanel::SetPanelColour( const DWORD Colour )
{ 
	//basic setting
	SetColorDWORD( Colour );

	//TODO: Apply setting to all relevant primitives
	TriangleStrip2D* pRect = (TriangleStrip2D*)singObjectLinker::instance().GetObject( m_IDPanelBottom );
	pRect->UpdateColor( Colour );	
}

//multi color panel
void SquarePanel::SetPanelColour( const DWORD ColourLT, const DWORD ColourRest )
{
	//basis color as main color
	SetColorDWORD( ColourRest );

	//Set color to relevant vertex
	POINT PanelPos = GetPosLT();
	//Draw primitive size by its visual size
	POINT PanelSize = m_PosVisualSize;

	TriangleStrip2D* pRect = (TriangleStrip2D*)singObjectLinker::instance().GetObject( m_IDPanelBottom );
	POINT2D Vertexes[4] = 
	{
		{PanelPos.x, PanelPos.y								, ColourLT},
		{PanelPos.x + PanelSize.x, PanelPos.y				, ColourRest},
		{PanelPos.x, PanelPos.y + PanelSize.y				, ColourRest},
		{PanelPos.x + PanelSize.x, PanelPos.y + PanelSize.y	, ColourRest}
	};
	pRect->UpdatePos( Vertexes, 4, true );
}

void SquarePanel::SetPanelPosLT( const POINT &PosLT )
{ 
	//basic setting
	SetPosLT( PosLT ); 

	//TODO: Apply setting to all relevant primitives
	PanelObjectPosUpdate();
}

void SquarePanel::SetPanelSize( const POINT &Size ) 
{ 
	//basic setting
	SetSize( Size ); 

	//TODO: Apply setting to all relevant primitives
	PanelObjectPosUpdate();
}

//Real time logic function
void SquarePanel::RealTimeLogic(void)
{
	//TODO: real time stuffs here
	switch( m_MyState )
	{
	case PanelOpening:
		ProceedOpening();
		break;
	case PanelClosing:
		ProceedClosing();
		break;
	}

	//RTL basis
	//suppose to run all RTL in all involved object
	list<Object*>::iterator itr;
	list<Object*>::iterator itr_end = m_Objects.end();
	for ( itr = m_Objects.begin(); itr != itr_end; ++itr )
	{
		(*itr)->RealTimeLogic();
	}

}

void SquarePanel::MouseClickAt( const POINT &posMouse )
{
	const int iCloseScale = 10;

	if( m_posLT.x < posMouse.x  && posMouse.x < m_posLT.x + iCloseScale 
		&& m_posLT.y < posMouse.y && posMouse.y < m_posLT.y + iCloseScale )
		ClosePanel();

	return;
}
void SquarePanel::MouseMoveAt( const POINT &posMouse )
{
	return;
}
void SquarePanel::KeyDown( const WPARAM &wKey )
{
	return;
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//unique funs
void SquarePanel::OpenPanel(void)
{
	if( PanelOpening == m_MyState )
		return;

	//TODO:Start the Opening
	SwitchToState( PanelOpening );
	
}

void SquarePanel::ClosePanel(void)
{
	if( PanelClosing == m_MyState )
		return;

	//TODO:Start the Opening
	SwitchToState( PanelClosing );
	
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//private tool funs
void SquarePanel::PanelObjectPosUpdate()
{
	//Update the position of all relevant primitives or objects
	POINT PanelPos = GetPosLT();
	//Draw primitive size by its visual size
	POINT PanelSize = m_PosVisualSize;

	//Panel bottom
	TriangleStrip2D* pRect = (TriangleStrip2D*)singObjectLinker::instance().GetObject( m_IDPanelBottom );
	POINT2D Vertexes[4] = 
	{
		{PanelPos.x, PanelPos.y},
		{PanelPos.x + PanelSize.x, PanelPos.y},
		{PanelPos.x, PanelPos.y + PanelSize.y},
		{PanelPos.x + PanelSize.x, PanelPos.y + PanelSize.y}
	};
	pRect->UpdatePos( Vertexes, 4 );	
}

void SquarePanel::ProceedOpening()
{
	const POINT ActualSize = GetSize();
	POINT VisualSize = m_PosVisualSize;
	const LONG lExtensionUnitX = ActualSize.x / iPanelOpenFrames;
	const LONG lExtensionUnitY = ActualSize.y / iPanelOpenFrames;

	if( VisualSize.x < ActualSize.x )
	{
		//do X axis extension here
		m_PosVisualSize.x += lExtensionUnitX;
		m_PosVisualSize.y += lExtensionUnitY;
		PanelObjectPosUpdate();
	}
	else
	{
		//Size secure
		m_PosVisualSize.x = ActualSize.x;
		m_PosVisualSize.y = ActualSize.y;
		PanelObjectPosUpdate();
		//Opening finish
		SwitchToState( PanelNormal );
	}
}

void SquarePanel::ProceedClosing()
{
	const POINT ActualSize = GetSize();
	POINT VisualSize = m_PosVisualSize;
	LONG lExtensionUnitX = ActualSize.x / iPanelOpenFrames;
	LONG lExtensionUnitY = ActualSize.y / iPanelOpenFrames;

	if( 0 == lExtensionUnitX )
		lExtensionUnitX = 1;
	if( 0 == lExtensionUnitY )
		lExtensionUnitY = 1;

	if( VisualSize.x > lExtensionUnitX )
	{
		//do X axis extension here
		m_PosVisualSize.x -= lExtensionUnitX;
		PanelObjectPosUpdate();
	}
	else if ( m_sClosingPercent <= iPanelWaitFrames )
	{
		//wait here
		++m_sClosingPercent;
	}
	else if( VisualSize.y > lExtensionUnitY )
	{
		//DO Y axis extension here
		m_PosVisualSize.y -= lExtensionUnitY;
		PanelObjectPosUpdate();
	}
	else
	{
		//Size secure
		m_PosVisualSize.x = 0;
		m_PosVisualSize.y = 0;
		m_sClosingPercent = 0;
		PanelObjectPosUpdate();
		//Opening finish
		SwitchToState( PanelInvisible );
	}
}

void SquarePanel::SwitchToState( ns_SquarePanel::PanelState State )
{
	//TODO: doing state switch here
	m_MyState = State;

	switch( m_MyState )
	{
	case PanelOpening:
		SetVisible( true );
		m_bPanelLocked = true;
		break;
	case PanelClosing:
		m_bPanelLocked = true;
		break;
	case PanelNormal:
		m_bPanelLocked = false;
		break;
	case PanelMinimized:
		m_bPanelLocked = true;
		break;
	case PanelInvisible:
		m_bPanelLocked = true;
		SetVisible( false );
		break;

	default:
		break;
	}	
}
