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
#include "PhaseFactory.h"

//------------------------------------------------------------
//	Implement
//------------------------------------------------------------

//------------------------------------------------------------
PhaseFactory::PhaseFactory( void )
{
	// nothing here
}
//------------------------------------------------------------
PhaseFactory::~PhaseFactory( void )
{
	// nothing here
}
//------------------------------------------------------------
bool PhaseFactory::Register( const char *pType, tCreator aCreator )
{
	string str = string( pType );
	return m_Creators.insert( make_pair( str, aCreator )).second;
}
//------------------------------------------------------------
Phase *PhaseFactory::Create( const char *pType )
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
