#include ".\ObjectLinker.h"

ObjectLinker::ObjectLinker(void)
{
	m_iMaxID = 0;
}

ObjectLinker::~ObjectLinker(void)
{
}

int ObjectLinker::GetRegID( Object* pObj )
{
	//if Pointer is null, directly return
	if( NULL == pObj )
		return -1;

	//check the pointer has been registed or not
	RegMap::iterator map_itr = m_mapRegID.begin();
	RegMap::iterator itr_end = m_mapRegID.end();
	bool PointerIsRegisted = false;

	for( ; map_itr != itr_end; ++map_itr )
	{
		if( (*map_itr).second == pObj )
		{
			PointerIsRegisted = true;
			break;
		}
	}
	if( PointerIsRegisted )
	{
		return (*map_itr).first;
	}
	else
	{
		return RegNewObject( pObj );
	}
}
int ObjectLinker::RegNewObject( Object* pObj )
{
	//check for vacancy
	RegMap::iterator map_itr = m_mapRegID.begin();
	RegMap::iterator itr_end = m_mapRegID.end();
	for( ; map_itr != itr_end; ++map_itr )
	{
		if( NULL == (*map_itr).second )
		{
			(*map_itr).second = pObj;
			return (*map_itr).first;
		}
	}

	//if no vacancy add new peer
	++m_iMaxID;
	m_mapRegID.insert( make_pair(m_iMaxID, pObj) );
	return m_iMaxID;
}
Object* ObjectLinker::GetObject( int iID )
{
	if( iID > m_iMaxID || iID < 1)
		return NULL;

	RegMap::iterator itr = m_mapRegID.find( iID );

	return (*itr).second;
}

bool ObjectLinker::RemoveObject( Object* pObj )
{
	//Find and remove
	RegMap::iterator map_itr = m_mapRegID.begin();
	RegMap::iterator itr_end = m_mapRegID.end();
	for( ; map_itr != itr_end; ++map_itr )
	{
		if( pObj == (*map_itr).second )
		{
			(*map_itr).second = NULL;
			return true;
		}
	}

	return false;
}
