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
	/* �ⲿ���õ���Ⱦ������ͳһ�ӿڣ�����OBJECT����ָ�룬�п��ܻ��޸�OBJ����                                                                     */
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
	/* �����������                                                                     */
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
	/* ����β�������                                                                     */
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
	/* �ַ��������                                                                     */
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
	/* ��ǰ�����Ƿ��ý���                                                                     */
	/************************************************************************/
	bool m_bFocus;
	int m_iLoadingID;

	/************************************************************************/
	/* �����ʹ��                                                                     */
	/************************************************************************/
	bool m_bDirty;
	/************************************************************************/
	/* �����б��Զ�����Ⱦʱʹ��                                                                     */
	/************************************************************************/
	DrawComponent* m_pHeadComponent;
	/************************************************************************/
	/* ��Դ·��                                                                     */
	/************************************************************************/
	vector<string>m_vctPicRes;
	/************************************************************************/
	/* ������Դ                                                                     */
	/************************************************************************/
	//����ߴ�
	vector<int>m_vctFontSize;
	//��������
	vector<string>m_vctFontType;
	//������
	vector<bool>m_vctFontThick;
	//б����
	vector<bool>m_vctFontTrend;
};

#endif // !defined(AFX_CANVAS_H__00D2F0BB_1138_48B4_8977_DCA5A44FC6F3__INCLUDED_)
