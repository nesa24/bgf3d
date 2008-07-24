#pragma once
#include <map>
#include "Object.h"

using namespace std;
class ObjectLinker
{
	typedef map< int, Object*> RegMap;
public:
	ObjectLinker(void);
	~ObjectLinker(void);

	int GetRegID( Object* pObj );
	int RegNewObject( Object* pObj );
	Object* GetObject( int iID );
	bool RemoveObject( Object* pObj );

private:
	RegMap m_mapRegID;
	int m_iMaxID;
};
