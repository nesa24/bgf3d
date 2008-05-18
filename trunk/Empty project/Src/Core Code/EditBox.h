// EditBox.h: interface for the EditBox class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EDITBOX_H__3DB61CC2_B759_44C2_8792_05263F07E060__INCLUDED_)
#define AFX_EDITBOX_H__3DB61CC2_B759_44C2_8792_05263F07E060__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ObjUI.h"
#include "TextBox.h"

class EditBox : public ObjUI  
{
public:
	/************************************************************************/
	/* get input infomation                                                                     */
	/************************************************************************/
	void GetChar( UINT nChar );

	/************************************************************************/
	/* focus                                                                     */
	/************************************************************************/
	void MouseLClick( void );

	int GetMaxLength() const;
	void SetVisible( const bool bVisible );

	/************************************************************************/
	/* lock & unlock input                                                                     */
	/************************************************************************/
	bool GetLock() const;
	void SetLock( bool block );

	/************************************************************************/
	/* update string display                                                                     */
	/************************************************************************/
	bool UpdateData();

	/************************************************************************/
	/* return input char                                                                     */
	/************************************************************************/
	char* GetCharBuffer();

	/************************************************************************/
	/* create static text for display                                                                      */
	/************************************************************************/
	bool InitFinish( int iid, int charlength = 20, int red = 0, int green = 0, int blue = 0 );

	bool ClearBuffer();
	int GetEditNumber();
	void SetMaxLength( const int &charlength );

	/************************************************************************/
	/* set line display char number                                                                     */
	/************************************************************************/
	inline void SetCharLength( int charlength )
	{
		m_MyText->SetCharLength( charlength );
	}

	static Object* CreateObject( void )
	{
		return (Object*) new EditBox;
	}

	/************************************************************************/
	/* draw it's static text                                                                     */
	/************************************************************************/
	bool Draw(Canvas* pCanvas);

	EditBox();
	virtual ~EditBox();

	ObjectType GetObjectType( void ) const
	{
		return ObjectEditBox;
	}

	void SetPassWord( const bool pw )
	{
		m_bPassWord = pw;
	}
protected:
	bool m_bLock;
	bool m_bPassWord;
	char m_cSor;
	int m_iInit;
	int m_iMax;
	int m_iMaxLength;
	StaticText* m_MyText;
	char m_cShow[MAX_PATH];

};

#endif // !defined(AFX_EDITBOX_H__3DB61CC2_B759_44C2_8792_05263F07E060__INCLUDED_)
