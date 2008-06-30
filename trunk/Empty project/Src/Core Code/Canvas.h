// Canvas.h: interface for the Canvas class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CANVAS_H__00D2F0BB_1138_48B4_8977_DCA5A44FC6F3__INCLUDED_)
#define AFX_CANVAS_H__00D2F0BB_1138_48B4_8977_DCA5A44FC6F3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include <string>
#include "Object.h"
#include "../Graphics/GameGraphics.h"

using namespace std;

class DrawComponent;

class Canvas  
{
public:
	Canvas();
	virtual ~Canvas();
	/************************************************************************/
	/* 外部调用的渲染函数，统一接口，传入OBJECT对象指针，有可能会修改OBJ对象                                                                     */
	/************************************************************************/
	int DrawObject( Object* pObj );
	void RenderLoad();
	BOOL CreateCanvas();
	void ShutCanvas();
	BOOL InitCanvas();
	void Render();
	CGameGraphics* GetGraphics() const;
	void DrawRect( RECT &rect, float layer, int size = 1, DWORD color = 0xff00ff00 );

	/************************************************************************/
	/* 焦点操作函数                                                                     */
	/************************************************************************/
	inline void SetCanvasFocus( const bool bfocus )
	{
		m_bFocus = bfocus;
	}
	inline bool GetCanvasFocus() const
	{
		return m_bFocus;
	}

	inline void AddPicRes( string filename )
	{
		m_vctPicRes.push_back( filename );
	}

	inline int GetPicResNbr()
	{
		return (int)m_vctPicRes.size();
	}

	/************************************************************************/
	/* 脏矩形操作函数                                                                     */
	/************************************************************************/
	inline void SetDirty( const bool bdirty )
	{
		m_bDirty = bdirty;
	}
	inline bool GetDirty() const
	{
		return m_bDirty;
	}

	/************************************************************************/
	/* 字符方面操作                                                                     */
	/************************************************************************/
	inline void AddFontSize( int isize )
	{
		m_vctFontSize.push_back( isize );
	}
	inline void AddFontType( string filename )
	{
		m_vctFontType.push_back( filename );
	}
	inline void AddFontThick( bool bthick )
	{
		m_vctFontThick.push_back( bthick );
	}
	inline void AddFontTrend( bool btrend )
	{
		m_vctFontTrend.push_back( btrend );
	}

	inline void AddFont( int isize, string filename, bool bthick, bool btrend )
	{
		AddFontSize( isize );
		AddFontType( filename );
		AddFontThick( bthick );
		AddFontTrend( btrend );
	}

	inline int GetFontSize( const int iID )
	{
		if ( iID < 0 || iID >= (int)(m_vctFontSize.size()) )
			return 0;

		return m_vctFontSize[iID];
	}


private:
	CGameGraphics*		m_pGameGraphics;
	/************************************************************************/
	/* 当前程序是否获得焦点                                                                     */
	/************************************************************************/
	bool m_bFocus;
	int m_iLoadingID;

	/************************************************************************/
	/* 脏矩形使用                                                                     */
	/************************************************************************/
	bool m_bDirty;
	/************************************************************************/
	/* 动画列表，对对象渲染时使用                                                                     */
	/************************************************************************/
	DrawComponent* m_pHeadComponent;
	/************************************************************************/
	/* 资源路径                                                                     */
	/************************************************************************/
	vector<string>m_vctPicRes;
	/************************************************************************/
	/* 字体资源                                                                     */
	/************************************************************************/
	//字体尺寸
	vector<int>m_vctFontSize;
	//字体类型
	vector<string>m_vctFontType;
	//粗体字
	vector<bool>m_vctFontThick;
	//斜体字
	vector<bool>m_vctFontTrend;
};

#endif // !defined(AFX_CANVAS_H__00D2F0BB_1138_48B4_8977_DCA5A44FC6F3__INCLUDED_)
