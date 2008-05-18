// GameGraphics.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "GameGraphics.h"

char g_strError_Report_Buffer[MAX_PATH];

// This is the constructor of a class that has been exported.
// see GameGraphics.h for the class definition
CGameGraphics::CGameGraphics()
{ 
	return; 
}


GraphicsError CGameGraphics::CreateSurface(int width, int height)
{
	//Write Error Report
	sprintf( g_strError_Report_Buffer, "CreateSurface()" );
	//
	return ERR_VIRTUAL;
}

GraphicsError CGameGraphics::ShutGraphics()
{
	//Write Error Report
	sprintf( g_strError_Report_Buffer, "ShutGraphics()" );
	//
	return ERR_VIRTUAL;
}

GraphicsError CGameGraphics::LoadPic(int iID, char *filename)
{
	//Write Error Report
	sprintf( g_strError_Report_Buffer, "LoadPic()" );
	//
	return ERR_VIRTUAL;
}

GraphicsError CGameGraphics::InitGeometry()
{
	//Write Error Report
	sprintf( g_strError_Report_Buffer, "InitGeometry()" );
	//
	return ERR_VIRTUAL;
}

GraphicsError CGameGraphics::SetupMatrices()
{
	//Write Error Report
	sprintf( g_strError_Report_Buffer, "SetupMatrices()" );
	//
	return ERR_VIRTUAL;
}

GraphicsError CGameGraphics::DXCreateFont( int iSize, char *strType, BOOL bBold, BOOL bSharp )
{
	//Write Error Report
	sprintf( g_strError_Report_Buffer, "DXCreateFont()" );
	//
	return ERR_VIRTUAL;
}

GraphicsError CGameGraphics::FillSurface(int iID, DWORD color)
{
	//Write Error Report
	sprintf( g_strError_Report_Buffer, "FillSurface()" );
	//
	return ERR_VIRTUAL;
}

GraphicsError CGameGraphics::FillSurfaceRect( int iID, DWORD color, LPRECT lpR )
{
	//Write Error Report
	sprintf( g_strError_Report_Buffer, "FillSurfaceRect()" );
	//
	return ERR_VIRTUAL;
}

GraphicsError CGameGraphics::BeginRender()
{
	//Write Error Report
	sprintf( g_strError_Report_Buffer, "BeginRender()" );
	//
	return ERR_VIRTUAL;
}

GraphicsError CGameGraphics::EndRender()
{
	//Write Error Report
	sprintf( g_strError_Report_Buffer, "EndRender()" );
	//
	return ERR_VIRTUAL;
}

GraphicsError CGameGraphics::Render()
{
	//Write Error Report
	sprintf( g_strError_Report_Buffer, "Render()" );
	//
	return ERR_VIRTUAL;
}

GraphicsError CGameGraphics::PrintText(int iID, int x, int y, char *text, DWORD color, int iwidth, int isize_x, int isize_y )
{
	//Write Error Report
	sprintf( g_strError_Report_Buffer, "PrintText()" );
	//
	return ERR_VIRTUAL;
}

GraphicsError CGameGraphics::Draw2D_Base(int iDescID, int iSrcID, int x, int y, float z, LPRECT lpRect)
{
	//Write Error Report
	sprintf( g_strError_Report_Buffer, "Draw2D_Base()" );
	//
	return ERR_VIRTUAL;
}

GraphicsError CGameGraphics::Draw2D_Advance(int iDescID, int iSrcID, int x, int y, float z, LPRECT lpdesc_rect, LPRECT lpsrc_rect, DWORD color, int alpha, int angle, float size_x, float size_y)
{
	//Write Error Report
	sprintf( g_strError_Report_Buffer, "Draw2D_Advance()" );
	//
	return ERR_VIRTUAL;
}

GraphicsError CGameGraphics::Draw2D_Alpha(int iDescID, int iSrcID, int x, int y, float z, LPRECT lpdesc_rect, LPRECT lpsrc_rect, DWORD color, int alpha)
{
	//Write Error Report
	sprintf( g_strError_Report_Buffer, "Draw2D_Alpha()" );
	//
	return ERR_VIRTUAL;
}

GraphicsError CGameGraphics::ReleaseSurface(int iID)
{
	//Write Error Report
	sprintf( g_strError_Report_Buffer, "ReleaseSurface()" );
	//
	return ERR_VIRTUAL;
}

GraphicsError CGameGraphics::InitGraphics( HWND hwnd, BOOL bWindow, int width, int height )
{
	//Write Error Report
	sprintf( g_strError_Report_Buffer, "InitGraphics()" );
	//
	return ERR_VIRTUAL;
}

GraphicsError CGameGraphics::BeginSprite()
{
	//Write Error Report
	sprintf( g_strError_Report_Buffer, "BeginSprite()" );
	//
	return ERR_VIRTUAL;
}

GraphicsError CGameGraphics::EndSprite()
{
	//Write Error Report
	sprintf( g_strError_Report_Buffer, "EndSprite()" );
	//
	return ERR_VIRTUAL;
}


// create surface(texture) form file in memory
GraphicsError CGameGraphics::LoadPicFromFileInMemory(int iID, LPCVOID pSrcData, UINT SrcDataSize)
{
	//Write Error Report
	sprintf( g_strError_Report_Buffer, "LoadPicFromFileInMemory()" );
	//
	return ERR_VIRTUAL;
}

GraphicsError CGameGraphics::ReleasePicSurface( int iID )
{
	//Write Error Report
	sprintf( g_strError_Report_Buffer, "ReleaseSurface()" );
	//
	return ERR_VIRTUAL;
}

GraphicsError CGameGraphics::SaveSurfaceToFile( char* filename, const int SaveType, LPRECT lpSrcRect )
{
	//Write Error Report
	sprintf( g_strError_Report_Buffer, "SaveSurfaceToFile()" );
	//
	return ERR_VIRTUAL;
}

// lock surface
GraphicsError CGameGraphics::LockSurface( const int iID, LPRECT lprect, BYTE* &pByte, int &pitch )
{
	//Write Error Report
	sprintf( g_strError_Report_Buffer, "LockSurface()" );
	//
	return ERR_VIRTUAL;
}

// unlock surface
GraphicsError CGameGraphics::UnlockSurface( const int iID )
{
	//Write Error Report
	sprintf( g_strError_Report_Buffer, "UnlockSurface()" );
	//
	return ERR_VIRTUAL;
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ly's added
GraphicsError CGameGraphics::Draw2DShape( ShapeType theType, void* pVertexBuffer, int iPrimitiveNumber)
{
	//Write Error Report
	sprintf( g_strError_Report_Buffer, "UnlockSurface()" );
	//
	return ERR_VIRTUAL;

}

GraphicsError CGameGraphics::CreateVertexBuffer( void** ppBuffer, int iBufferSize, bool b2DBuffer)
{
	//Write Error Report
	sprintf( g_strError_Report_Buffer, "UnlockSurface()" );
	//
	return ERR_VIRTUAL;
}

GraphicsError CGameGraphics::UpdateVertexBuffer( void* pVertex, void* pBuffer, size_t Size )
{
	//Write Error Report
	sprintf( g_strError_Report_Buffer, "UnlockSurface()" );
	//
	return ERR_VIRTUAL;
}



//ly's adde end
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	