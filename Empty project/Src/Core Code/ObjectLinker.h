#pragma once
#include <map>
#include "Object.h"

using namespace std;
class ObjectLinker
{
	typedef map< long, Object*> RegMap;
public:
	ObjectLinker(void);
	~ObjectLinker(void);

	long GetRegID( Object* pObj );
	long RegNewObject( Object* pObj );
	Object* GetObject( long iID );
	bool RemoveObject( Object* pObj );
	void ClearAll();

private:
	RegMap m_mapRegID;
	long m_iMaxID;
};
