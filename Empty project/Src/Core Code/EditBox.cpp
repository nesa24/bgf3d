// EditBox.cpp: implementation of the EditBox class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "EditBox.h"
#include <errno.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

EditBox::EditBox()
{
	m_bLock = true;
	m_bPassWord = false;
	m_iMaxLength = ConstStuff::TEXT_DEFAULT_ROW_WORD_NBR;
	m_MyText = NULL;
	sprintf( m_cShow, "" );
}

EditBox::~EditBox()
{
} 

void EditBox::GetChar(UINT nChar)
{
	//lock can't input
	if ( m_bLock )
		return;

	string save;
	save = (string)m_cShow;

	if ( nChar == VK_TAB || nChar == VK_RETURN )
		return;

	//点击退格键
	if ( nChar == '\b' )
	{
		int len = strlen( m_cShow );

		if ( len == 0 )
			return;
		else if ( len == 1 )
		{
			m_cShow[0] = '\0';
			return;
		}
		else
		{
			BYTE cc1, cc2;
			cc1 = m_cShow[ len - 1 ];
			cc2 = m_cShow[ len - 2 ];

			if ( cc1 > 0xA0 && cc2 > 0xA0 )//zhongwen
				m_cShow[ len - 2 ] = '\0';
			else
				m_cShow[ len - 1 ] = '\0';
			
			return;
		}
	}

	if ( save.length() >= m_iMaxLength )
		return;
		
	if ( IsDBCSLeadByte( nChar ) ) 
	{
		static char c2[2];
		static int pos = 0;
		if ( pos == 0 )
		{
			c2[0] = nChar;
			pos++;
		}
		else
		{
			c2[1] = nChar;
			pos = 0;
			save += (string)c2;
			sprintf( m_cShow, "%s", save.c_str() );
		}
		
	}
	else
	{
		char c1[4] = "";
		c1[0] =	(unsigned char)nChar;
		string temp = save;
		temp += (string)c1;
		sprintf( m_cShow, "%s", temp.c_str() );
	}
}

int EditBox::GetEditNumber()
{
	int nbr = atoi( m_cShow );

	//overflow
	if ( errno == ERANGE )
	{
		return 0;
	}

	return nbr;
}

bool EditBox::ClearBuffer()
{
	memset( m_cShow, 0, sizeof( m_cShow ) );
	return true;
}

bool EditBox::InitFinish( int iid, int charlength, int red, int green, int blue )
{
	POINT pos = GetPosLT();
	pos.x += 5;
	pos.y += 5;
	m_MyText = (StaticText*)singObjectFactory::instance().Create( "StaticText" );
	m_MyText->SetPosLT( pos );
	m_MyText->SetTextID( iid );
	m_MyText->SetCharLength( charlength );
	m_MyText->SetColorRGB( red, green, blue );
	m_MyText->SetVisible( GetVisible() );
	m_MyText->SetSize( GetSize() );

	if ( m_MyText == NULL )
		return false;

	return true;
}

char* EditBox::GetCharBuffer()
{
	return m_cShow;
}

bool EditBox::UpdateData()
{
	char showtex[MAX_PATH];
	int length = strlen( m_cShow );
	memset( showtex, 0, sizeof(showtex) );
	int charlength = m_MyText->GetTextLineSize() - 1;
	if ( length > charlength )
	{
		int i = 0;
		//只显示部分
		for ( ; i < length - charlength; )
		{
			if ( m_cShow[i] < 0 )
				i++;
			++i;
		}
		if ( m_bPassWord )
		{
			for ( int j = 0; j < charlength; ++j )
			{
				showtex[j] = '*';
			}

		}
		else
		{
			memcpy( showtex, &m_cShow[i], charlength );
		}
		showtex[charlength] = m_cSor;
	}
	else
	{
		if ( m_bPassWord )
		{
			for ( int i = 0; i < length; ++i )
			{
				showtex[i] = '*';
			}

		}
		else
		{
			memcpy( showtex, m_cShow, length );
		}
		showtex[length] = m_cSor;
	}

	string save;
	save = (string)showtex;
	m_MyText->SetContentStr( save );

	return true;
}


void EditBox::SetLock(bool block)
{
	m_bLock = block;

	if ( block )
		m_cSor = ' ';
	else
		m_cSor = '|';

	UpdateData();
}

bool EditBox::GetLock() const
{
	return m_bLock;
}

void EditBox::SetMaxLength( const int &charlength )
{
	m_iMaxLength = charlength;
}

void EditBox::SetVisible( const bool bVisible )
{
	m_bVisible = bVisible;
	if ( m_MyText )
		m_MyText->SetVisible( bVisible );
}

int EditBox::GetMaxLength() const
{
	return m_iMaxLength;
}

bool EditBox::Draw(Canvas* pCanvas)
{
	if ( m_MyText )
	{
		//UpdateData();
		m_MyText->Draw( pCanvas );
	}

	Object::Draw( pCanvas );

	return true;
}

void EditBox::MouseLClick( void )
{
	SetLock( false );
}


