#pragma once
#include "panel.h"

const POINT SquarePanelDefaultPos  = {10,  10};
const POINT SquarePanelDefaultSize = {120, 90};

namespace ns_SquarePanel
{
	enum PanelState
	{
		PanelOpening,
		PanelClosing,
		PanelNormal,
		PanelMinimized,
		PanelInvisible,

		//number of state
		StateNbr
	};
};


class SquarePanel :
	public Panel
{
public:
	SquarePanel(void);
	~SquarePanel(void);
	//basic override
	static Object* CreateObject( void )
	{
		return (Object*)new SquarePanel;
	}
	ObjectType GetObjectType( void ) const 
	{ 
		return ObjectSquarePanel; 
	};
	
	//Override from panel
	void SetPanelPosLT( const POINT &PosLT );
	void SetPanelColour( const DWORD Colour );
	void SetPanelColour( const DWORD ColourLT, const DWORD ColourRest );
	void SetPanelSize( const POINT &Size );
	void RealTimeLogic(void);
	void MouseClickAt( const POINT &posMouse );
	void MouseMoveAt( const POINT &posMouse );
	void KeyDown( const WPARAM &wKey );

	//unique funs
	void OpenPanel(void);
	void ClosePanel(void);

private:
	//Private tools
	void PanelObjectPosUpdate(void);
	void ProceedOpening();
	void ProceedClosing();
	void SwitchToState( ns_SquarePanel::PanelState State );


private:
	long m_IDPanelBottom;
	POINT m_PosVisualSize;
	ns_SquarePanel::PanelState m_MyState;
	bool m_bPanelLocked;
	unsigned short m_sOpeningPercent;
	unsigned short m_sClosingPercent;
};
