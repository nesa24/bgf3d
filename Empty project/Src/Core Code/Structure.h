/** @file	Structure.h
	@brief	This file is ONLY for structure
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

//------------------------------------------------------------
//	Include
//------------------------------------------------------------
#ifndef STRUCTURE_H_BOK
#define STRUCTURE_H_BOK

//------------------------------------------------------------
//	Typedef
//------------------------------------------------------------

typedef struct PicLocation_tag
{
	unsigned short m_iPicID;
	unsigned short m_iTop;
	unsigned short m_iLeft;
	unsigned short m_iBottom;
	unsigned short m_iRight;
} PicLocation;


#endif
