#include "TextBox.h"

StaticText::StaticText( void )
{
	m_iLine = 0;
	m_iCharLength = 0;
	m_iTextID = 0;
	m_iShowLine = 3;
};

string StaticText::GetContentStr()
{
	int length = (int)m_strContent.size();
	int pos = m_iLine * m_iCharLength;
	int showline = m_iShowLine * m_iCharLength;
	if ( length <= pos )
		return m_strContent;

	char* pchar = (char*)m_strContent.c_str();
	int i = 0;
	for ( ; i < pos; ++i )
	{
		if ( *pchar < 0 )
		{
			pchar++;
			i++;
		}
		pchar++;
	}
	char * pendchar = pchar;
	int j = 0;
	for ( ; j < showline; ++j )
	{
		if( *pendchar < 0 )
		{
			pendchar++;
			j++;
		}
		pendchar++;
	}

	string getstr = m_strContent.substr( i, j );
	getstr+='\0';
	return getstr;
}

void StaticText::SetLine( int iline )
{
	if ( iline < 0 )
		iline = 0;

	int max_char = ( 1 + iline )  * m_iCharLength;
	int length = (int)m_strContent.size();
	if ( max_char > length )
	{
		iline = length / m_iCharLength;
	}

	m_iLine = iline;
}
