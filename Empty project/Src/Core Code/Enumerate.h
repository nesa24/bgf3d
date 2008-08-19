/** @file	Enumerate.h
	@brief	This file is ONLY for enumeration
	@author
		jMulrO BOK
	@date
		July 22, 2006
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

//------------------------------------------------------------
//	Include
//------------------------------------------------------------
#ifndef ENUMERATE_H_BOK
#define ENUMERATE_H_BOK

//------------------------------------------------------------
//	Enum
//------------------------------------------------------------

/*!
* \enum ObjectType
* \brief All Type of Objects
*/
enum ObjectType
{
		ObjectBase = 0,
		ObjectUI,
        ObjectButton,        
		ObjectEditBox,
		ObjectRichEditBox,
        ObjectImageCopy,
        ObjectStaticImage,
		ObjectMap,
		ObjectSubMap,	
		ObjectStaticText,

		ObjectPanel,
		ObjectSquarePanel,

		ObjectSprite,

		ObjectPrimitveShape,

		//Number of items
        NbrOfObject
};

enum InputType
{
	MouseClick = 0,
	MouseRelease,
	RMouseRelease,
	MouseMove,
	KeyDown,
	NetInput,
	CharInput,

	//Number of items
	NbrOfInput
};

#endif
