#ifndef GRAPHICSFUNS_H
#define GRAPHICSFUNS_H

#include "GameGraphics.h"
#include "GrahicsErr.h"

#define _DEBUG_GRAPHICS

//创建图形控制类
//参数:窗口句柄,是否全屏,全屏下的宽,全屏下的高
//外部直接调用此函数创建对象,不用直接调用CGameGraphics对象的初始化创建
CGameGraphics GAMEGRAPHICS_API  *CreateGameGraphics( HWND hwnd, BOOL bWindow, int width, int height );

bool GAMEGRAPHICS_API ReportError( GraphicsError error );

#endif

