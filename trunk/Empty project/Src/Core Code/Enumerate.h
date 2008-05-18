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

/** @brief	type of classes
 */
enum ClassType
{
	TypeObject = 0,
	TypeUI,
	TypeGameSpirit,
	TypeChess,
	TypeCard,
	TypeChessBoard,
	TypeButton,
	TypeStaticImage,
	TypeEditBox,
	TypeRichEdit,
	TypeStaticText,
	TypeListBox,

	TypePanel,

	TypeSprite,
};

/*!
* \enum ObjectType
* \brief All Type of Objects
*/
enum ObjectType
{
		ObjectBase = 0,
        ObjectButton,        
		ObjectEditBox,
		ObjectRichEditBox,
        ObjectImageCopy,
        ObjectStaticImage,
		ObjectMap,
		ObjectSubMap,	
		ObjectStaticText,

		ObjectPanel,

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
