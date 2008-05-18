// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
#define AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#define SAFE_DELETE(p) {delete p;p=NULL;}		// safe delete point
#define USE_PANEL_RANGE

#include <windows.h>

#include <queue>

// debug
#include "test.h"

#include "typedefs.h"
//
#include "assert.h"

//Class header
#include "Phase.h"
#include "TestPhase.h"

#include "GlobalFuns.h"
#include "ObjectFactory.h"
#include "PhaseFactory.h"

//Objects
#include "Object.h"
#include "Panel.h"
#include "GlobalStuff.h"
#include "Image.h"
#include "TextBox.h"
#include "EditBox.h"
#include "button.h"
#include "Sprite.h"

#include "Shape.h"
#include "Line2D.h"
#include "Point2D.h"
#include "TriangleStrip2D.h"

#include "ActionModule.h"

//Graphics
#include "../Graphics/GraphicsFuns.h"
#include "Canvas.h"
#pragma comment( lib, "GameGraphics.lib" )
//Audio
#include "../Audio/AudioFuns.h"
#include "Audio.h"
#pragma comment( lib, "GameAudio.lib" )

// Disable warnings
#pragma warning( disable:4786 )

#pragma comment( lib, "luabindlib_debug.lib" )

// luabind
#include <luabind/lua_include.hpp>
#include <luabind/luabind.hpp>
#include <luabind/class.hpp>



// TODO: reference additional headers your program requires here

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
