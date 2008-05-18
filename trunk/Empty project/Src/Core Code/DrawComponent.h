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

#ifndef DRAWCOMPONENT_H
#define DRAWCOMPONENT_H

#include "Object.h"
class Canvas;

/************************************************************************/
/* ���࣬������Ӷ����Ĺ��ܣ�ȫ���ǵ�̬
/************************************************************************/
class DrawComponent
{
public:
	DrawComponent* AddComponent( DrawComponent* pDC );
	virtual bool Link( DrawComponent* pDC ) = 0;
	virtual int Draw( Object* pObj, const Canvas* pCan ) = 0;
};

/************************************************************************/
/* ʵ��������Ⱦ����                                                                     */
/************************************************************************/
class DrawBasic:public DrawComponent
{
public:
	bool Link( DrawComponent* pDC );
	int Draw( Object* pObj, const Canvas* pCan );
};

/************************************************************************/
/* �������ֵĽṹ����������                                                                     */
/************************************************************************/
class DrawAnimation:public DrawComponent
{
public:
	bool Link( DrawComponent* pAM );
	virtual int Draw( Object* pObj, const Canvas* pCan ) = 0;
	DrawComponent* GetNextComponent() const
	{
		return m_pNextComponent;
	}
private:
	//ָ����һ����������
	DrawComponent* m_pNextComponent;
};

/************************************************************************/
/* x move                                                                     */
/************************************************************************/
class AnimationMoveX: public DrawAnimation
{
public:
	int Draw( Object* pObj, const Canvas* pCan );
};
/************************************************************************/
/* y move                                                                */
/************************************************************************/
class AnimationMoveY: public DrawAnimation
{
public:
	int Draw( Object* pObj, const Canvas* pCan );
};
/************************************************************************/
/* ��˸Ч��                                                                     */
/************************************************************************/
class AnimationAlpha: public DrawAnimation
{
public:
	int Draw( Object* pObj, const Canvas* pCan );
};

/************************************************************************/
/* ��תЧ��                                                                     */
/************************************************************************/

class AnimationCircumrotate: public DrawAnimation
{
public:
	int Draw( Object* pObj, const Canvas* pCan );
};

/************************************************************************/
/* ����Ч��                                                                     */
/************************************************************************/
class AnimationScale: public DrawAnimation
{
public:
	int Draw( Object* pObj, const Canvas* pCan );
};

/************************************************************************/
/* �붯��                                                                     */
/************************************************************************/
class AnimationFrame: public DrawAnimation
{
public:
	int Draw( Object* pObj, const Canvas* pCan );
};
#endif