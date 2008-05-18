#ifndef GLOBAL_STUFF_H
#define GLOBAL_STUFF_H

#include "Canvas.h"
#include "Audio.h"
#include <queue>
#include "ActionTypes.h"
#include <luabind/lua_include.hpp>

extern Canvas* g_pCanvas;
extern Audio*  g_pAudio;
extern HWND hwndMain;
extern lua_State* g_L;

extern lua_State* g_Data;

extern int g_iWindow_Width;
extern int g_iWindow_Height;

#endif