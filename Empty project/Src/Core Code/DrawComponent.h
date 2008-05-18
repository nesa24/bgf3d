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
/* 基类，具有添加动画的功能，全部是单态
/************************************************************************/
class DrawComponent
{
public:
	DrawComponent* AddComponent( DrawComponent* pDC );
	virtual bool Link( DrawComponent* pDC ) = 0;
	virtual int Draw( Object* pObj, const Canvas* pCan ) = 0;
};

/************************************************************************/
/* 实际最终渲染的类                                                                     */
/************************************************************************/
class DrawBasic:public DrawComponent
{
public:
	bool Link( DrawComponent* pDC );
	int Draw( Object* pObj, const Canvas* pCan );
};

/************************************************************************/
/* 动画部分的结构，带有链表                                                                     */
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
	//指想下一个动画类型
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
/* 闪烁效果                                                                     */
/************************************************************************/
class AnimationAlpha: public DrawAnimation
{
public:
	int Draw( Object* pObj, const Canvas* pCan );
};

/************************************************************************/
/* 旋转效果                                                                     */
/************************************************************************/

class AnimationCircumrotate: public DrawAnimation
{
public:
	int Draw( Object* pObj, const Canvas* pCan );
};

/************************************************************************/
/* 缩放效果                                                                     */
/************************************************************************/
class AnimationScale: public DrawAnimation
{
public:
	int Draw( Object* pObj, const Canvas* pCan );
};

/************************************************************************/
/* 针动画                                                                     */
/************************************************************************/
class AnimationFrame: public DrawAnimation
{
public:
	int Draw( Object* pObj, const Canvas* pCan );
};
#endif