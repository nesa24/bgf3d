#ifndef TEXTBOX_H
#define TEXTBOX_H 

#include "ObjUI.h"

class StaticText : public ObjUI
{
public:
	virtual ~StaticText( void ){};
	ObjectType GetObjectType( void ) const
	{
		return ObjectStaticText;
	}
	static Object* CreateObject( void )
	{
		return (Object*) new StaticText;
	}

	inline int GetTextID() const
	{
		return m_iTextID;
	}
	inline int GetTextLineSize() const
	{
		return m_iCharLength;
	}
	inline void SetContentStr( string strcontent )
	{
		m_strContent = strcontent;
	}
	string GetContentStr();
	inline int GetLine()
	{
		return m_iLine;
	}
	void SetLine( int iline );

	inline void SetCharLength( int charlength )
	{
		m_iCharLength = charlength;
	}
	inline void SetTextID( int iid )
	{
		m_iTextID = iid;
	}

protected:
	StaticText( void );
private:
	string m_strContent;
	int m_iLine;
	int m_iCharLength;
	int m_iTextID;
	int m_iShowLine;
};

#endif