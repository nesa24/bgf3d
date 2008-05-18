// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__54F58D9B_534F_441A_8029_5515B508517C__INCLUDED_)
#define AFX_STDAFX_H__54F58D9B_534F_441A_8029_5515B508517C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


// Insert your headers here
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "GrahicsErr.h"
#include "GraphicsFuns.h"
#include "Struct.h"

// TODO: reference additional headers your program requires here
#ifndef SAFE_RELEASE 
#define SAFE_RELEASE(p) { if(p){ p->Release(); p = NULL; }}
#define SAFE_DELETE(p)	{if (p) { delete p; p = NULL; }}
#endif
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__54F58D9B_534F_441A_8029_5515B508517C__INCLUDED_)
