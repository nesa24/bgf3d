// DX9Graphics.h: interface for the CDX9Graphics class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DX9GRAPHICS_H__CCB762D9_D35F_45BC_A1CF_43A98654F7D6__INCLUDED_)
#define AFX_DX9GRAPHICS_H__CCB762D9_D35F_45BC_A1CF_43A98654F7D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <d3d9.h>
#include <d3dx9.h>
#include <vector>

#include "GameGraphics.h"

#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "d3dx9.lib" )

using namespace std;

#define D3D9_CUSTOMVERTEX3D (D3DFVF_XYZ | D3DFVF_DIFFUSE)
#define D3D9_CUSTOMVERTEX2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)
 

class CDX9Graphics : public CGameGraphics  
{
public:
	GraphicsError PrintText(int iID, int x, int y, char *text, DWORD color, int iwidth = 60, int isize_x = 12, int isize_y = 20);
	GraphicsError EndSprite();
	GraphicsError BeginSprite();
	GraphicsError Draw2D_Base(int iDescID, int iSrcID, int x, int y, float z = 1.0f, LPRECT lpSrcRect = NULL );
	GraphicsError Draw2D_Alpha(int iDescID, int iSrcID, int x, int y, float z = 1.0f, LPRECT lpdesc_rect = NULL, LPRECT lpsrc_rect = NULL, DWORD color = 0xffffffff, int alpha = 0);
	GraphicsError Draw2D_Advance(int iDescID, int iSrcID, int x, int y, float z = 1.0f, LPRECT lpdesc_rect = NULL, LPRECT lpsrc_rect = NULL, DWORD color = 0xffffffff, int alpha = 0, int angle = 0, float size_x = 1.0f, float size_y = 1.0f);
	GraphicsError LoadPic( int iID, char* filename );
	GraphicsError CreateSurface( int width, int height );
	GraphicsError DXCreateFont( int iSize, char *strType, BOOL bBold = FALSE, BOOL bSharp = FALSE );
	GraphicsError InitGeometry();
	GraphicsError Render();
	GraphicsError SetupMatrices();
	GraphicsError FillSurface( int iID, DWORD color );
	GraphicsError FillSurfaceRect( int iID, DWORD color, LPRECT lpR = NULL );
	GraphicsError EndRender();
	GraphicsError BeginRender();
	GraphicsError ShutGraphics();
	GraphicsError InitGraphics( HWND hwnd, BOOL bWindow = TRUE, int width = 800, int height = 600 );
	// create surface(texture) form file in memory
	GraphicsError LoadPicFromFileInMemory(int iID, LPCVOID pSrcData, UINT SrcDataSize);
	// release surface(texture) 
	GraphicsError ReleasePicSurface( int iID );
	// only save the backbuffer
	GraphicsError SaveSurfaceToFile( char* filename, const int SaveType = SAVE_TYPE_JPG, LPRECT lpSrcRect = NULL );
	// lock surface
	GraphicsError LockSurface( const int iID, LPRECT lprect, BYTE* &pByte, int &pitch );
	// unlock surface
	GraphicsError UnlockSurface( const int iID );

	CDX9Graphics();
	virtual ~CDX9Graphics();

///////////////////////////
//ly's added
public:
	//orimitive present
	GraphicsError Draw2DShape( ShapeType theType, void* pVertexBuffer, int iPrimitiveNumber );
	GraphicsError Draw3DShape( ShapeType theType, void* pVertexBuffer, int iPrimitiveNumber );
	//vertex buffer control
	GraphicsError CreateVertexBuffer( void** ppBuffer, int iBufferSize, bool b2DBuffer);
	GraphicsError UpdateVertexBuffer( void* pVertex, void* pBuffer, size_t Size );
	void ReleaseVertexBuffer( void* pBuffer );
	//primitive control
	GraphicsError PrimitiveTranslate( float* pfRotate, float* pfPosition );
	//Camera control
	GraphicsError SetCamera( float* pfEyeVec, float* pfLookVec, float* pfUpVec );

private:
	//basic initiallization
	//** under alteration
	void InitMatrix();

	//primitive render
	GraphicsError DrawLine2D( IDirect3DVertexBuffer9* pVertexBuffer, int iPrimitiveNumber );
	GraphicsError DrawPoint2D( IDirect3DVertexBuffer9* pVertexBuffer, int iPrimitiveNumber );
	GraphicsError DrawTrianglestrip2D( IDirect3DVertexBuffer9* pVertexBuffer, int iPrimitiveNumber );

	GraphicsError DrawLine3D( IDirect3DVertexBuffer9* pVertexBuffer, int iPrimitiveNumber );
	GraphicsError DrawPoint3D( IDirect3DVertexBuffer9* pVertexBuffer, int iPrimitiveNumber );
	GraphicsError DrawTrianglestrip3D( IDirect3DVertexBuffer9* pVertexBuffer, int iPrimitiveNumber );

//ly's added end
///////////////////////////

private:
	HWND m_hWnd;
	LPDIRECT3D9 m_lpD3d;
	LPDIRECT3DDEVICE9 m_lpDev;
	vector<LPD3DXFONT>m_lppFont;
	LPD3DXSPRITE m_lpSpr;
	vector<LPDIRECT3DTEXTURE9>m_lppTex;
};

#endif // !defined(AFX_DX9GRAPHICS_H__CCB762D9_D35F_45BC_A1CF_43A98654F7D6__INCLUDED_)
