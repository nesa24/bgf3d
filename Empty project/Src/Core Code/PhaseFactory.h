/** @file ObjectFactory.h
	@brief A factory that produce object
	@author jMulrO BOK
	@date July 22, 2006
*/

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

#ifndef PHASEFACTORY_H_BOK
#define PHASEFACTORY_H_BOK

//------------------------------------------------------------
//	Include
//------------------------------------------------------------
#include <string>
#include <map>
#include "Object.h"
#include "Phase.h"

//------------------------------------------------------------
//	Namespace
//------------------------------------------------------------
using std::string;
using std::map;

//------------------------------------------------------------
//	Class
//------------------------------------------------------------

class PhaseFactory
{
	typedef Phase * (*tCreator)();
	typedef map<string, tCreator> tCreatorMap;

public:
	~PhaseFactory( void );

	bool Register( const char *pType, tCreator aCreator );
	Phase * Create( const char *pType );

protected:
	PhaseFactory( void );
	tCreatorMap m_Creators;
};

#endif
