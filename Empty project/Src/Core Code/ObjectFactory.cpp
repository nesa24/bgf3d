/*-----------------------------------------+      
|   @@@@@@@@@        @@@@@    @@@@@  @@@@@ |      
|   @@@@@@@@@@     @@@@@@@@   @@@@@  @@@@@ |      
|    @@     @@    @@@    @@@   @@    @@@   |      
|    @@     @@   @@@      @@   @@  @@@     |      
|    @@    @@    @@       @@   @@ @@@      |      
|    @@@@@@@    @@        @@   @@@@@@      |      
|   @@@@@@@@@   @@        @@  @@@@@@@@     |      
|   @@     @@@  @@       @@   @@@  @@@     |      
|   @@      @@  @@      @@@   @@    @@@    |      
|   @@      @@  @@@    @@@    @@     @@    |      
| @@@@@@@@@@@    @@@@@@@@   @@@@@@   @@@@  |      
| @@@@@@@@@@      @@@@@     @@@@@@    @@@  |      
+-----------------------------------------*/

//------------------------------------------------------------
//	Include 
//------------------------------------------------------------
#include "stdafx.h"
#include "ObjectFactory.h"

//------------------------------------------------------------
//	Implement
//------------------------------------------------------------

//------------------------------------------------------------
ObjectFactory::ObjectFactory( void )
{
	// nothing here
}
//------------------------------------------------------------
ObjectFactory::~ObjectFactory( void )
{
	// nothing here
}
//------------------------------------------------------------
bool ObjectFactory::Register( const char *pType, tCreator aCreator )
{
	string str = string( pType );
	return m_Creators.insert( make_pair( str, aCreator )).second;
}
//------------------------------------------------------------
Object *ObjectFactory::Create( const char *pType )
{
	tCreatorMap::iterator iter = m_Creators.find( string( pType ) ); 

	if( m_Creators.end() != iter )
	{
		tCreator aCreator = (*iter).second;
		return aCreator();
	}
	else
	{
		return NULL;
	}
}
//------------------------------------------------------------
