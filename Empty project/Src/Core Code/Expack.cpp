#include "expack.h"
#include "stdafx.h"

Expack::Expack(void)
{
	m_pNextPack = NULL;
}

Expack::~Expack(void)
{
	//release other pack
	SAFE_DELETE( m_pNextPack );
}


void Expack::AddPack(Expack* pPack)
{
	if( NULL == pPack )
		return;

	//don't add the added pack
	if( NULL != FindPack( pPack->GetPackName() ) )
		return;

	if( NULL == m_pNextPack )
	{
		m_pNextPack = pPack;
		return;
	}
	else
	{
		m_pNextPack->AddPack( pPack );
	}
}

Expack* Expack::FindPack( string strPackName )
{
	if( GetPackName() == strPackName )
		return (Expack*)this;
	else if( NULL != m_pNextPack )
		return m_pNextPack->FindPack( strPackName );
	else
		return NULL;
}


/////////////////////////////////////////////////////////////////////////////////////////
//base pack methods
BasePack::BasePack(void)
{
}

BasePack::~BasePack(void)
{
}
