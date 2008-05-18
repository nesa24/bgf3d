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

#ifndef OBJECTFACTORY_H_BOK
#define OBJECTFACTORY_H_BOK

//------------------------------------------------------------
//	Include
//------------------------------------------------------------
#include <string>
#include <map>
#include "Object.h"

//------------------------------------------------------------
//	Namespace
//------------------------------------------------------------
using std::string;
using std::map;

//------------------------------------------------------------
//	Class
//------------------------------------------------------------

/** @brief Object Factory class definition
	@warning none till now
	@bug none till now

	This class is the factory module. It will create a object instance by passing
	a name of the object you want. Also, this is a singleton class. You can access
	it anywhere you want. It's recommend you that create all object though this way.
*/
class ObjectFactory
{
	//------------------------------------------------------------
	//	Typedef
	//------------------------------------------------------------

	/** @brief	we use a tCreator to store the function pointer of creator
	*/
	typedef Object * (*tCreator)();

	/** @brief	we use a map to store the name of class and it's creator
	*/
	typedef map<string, tCreator> tCreatorMap;

public:
	//------------------------------------------------------------
	//	Destructor
	//------------------------------------------------------------

	/** @brief	Destructor
	*/
	~ObjectFactory( void );

	//------------------------------------------------------------
	//	For Factory Use Methods
	//------------------------------------------------------------

	/** @brief Register a class with a name
		@param	pType	a string that will used to create a object
		@param	aCreator	a function point indicate how to create special object
		@return return true if register successful, else false
		@warning Follow the syntax of creator: 
		Object *Object::createObject( void );

		Call this method to register you own class with the factory. Notice that
		there must be a static method in you own class that has no parameter,
		and will tell us the way to create an instance of you own class. Register
		it here, and then you can create an instance of you own class here.
	 */
	bool Register( const char *pType, tCreator aCreator );

	/** @brief Create an instance of appointed class
		@param	pType	a sting that indicate what type of class instance you want go create
		@return	return the pointer of instance if creating successful, else NULL
		@warning If the class is no registered, it will return NULL.

		Call this method to create an instance of your own class, if you have already
		register you class to this factory. Just pass the type, as a string, into 
		this method, then you will get what you want
	 */
	Object * Create( const char *pType );

protected:
	//------------------------------------------------------------
	//	Constructor
	//------------------------------------------------------------
	
	/** @brief	Constructor, private.
	 */
	ObjectFactory( void );

	//------------------------------------------------------------
	//	Data member
	//------------------------------------------------------------

	/// a map that holds the names and function pointers
	tCreatorMap m_Creators;
};

#endif
