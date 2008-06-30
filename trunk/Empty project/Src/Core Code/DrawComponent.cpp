#include "StdAfx.h"
#include "DrawComponent.h"

DrawComponent* DrawComponent::AddComponent( DrawComponent* pDC )
{
	pDC->Link( this );
	return pDC;
}

/************************************************************************/
/* DrawBasic's                                                                      */
/************************************************************************/
bool DrawBasic::Link( DrawComponent* pDC )
{	
	return true;
}

/************************************************************************/
/* 最后实际渲染OBJECT                                                                     */
/************************************************************************/
int DrawBasic::Draw( Object* pObj, const Canvas* pCan )
{
	if ( false == pObj->GetVisible() )
		return 1;

	/************************************************************************/
	/* print text                                                                     */
	/************************************************************************/
	if ( ObjectStaticText == pObj->GetObjectType() )
	{
		StaticText* pTextObj = (StaticText*)pObj;
		int OBJ_iID = pTextObj->GetTextID();
		DWORD OBJ_COLOR = pTextObj->GetColorDWORD();
		POINT OBJ_pntPos = pTextObj->GetPosLT();
		POINT OBJ_Size = pTextObj->GetSize();
		int charlength = pTextObj->GetTextLineSize();
		string str = pTextObj->GetContentStr();

		pCan->GetGraphics()->PrintText( OBJ_iID, OBJ_pntPos.x, OBJ_pntPos.y, (char*)str.c_str(), 
			OBJ_COLOR, charlength, OBJ_Size.y, OBJ_Size.y );

		return 0;
	}

	/////////////////////////////////////////////////////////
	//differ the render method of sprites and primitive shapes
	Shape* pShape = NULL;

	if( ObjectPrimitveShape == pObj->GetObjectType() )
	{
		pShape = (Shape*)pObj;
		if( pShape->Is3DShape() )
		{
			//Shape rotation
			pCan->GetGraphics()->PrimitiveTranslate( pShape->GetRotationSet(), pShape->GetPosition() );
			//draw 3D shape
			pCan->GetGraphics()->Draw3DShape( pShape->GetShapeType(), pShape->GetVertexBuffer(), pShape->GetPrimitiveNbr() );
		}
		else
		{
			pCan->GetGraphics()->Draw2DShape( pShape->GetShapeType(), pShape->GetVertexBuffer(), pShape->GetPrimitiveNbr() );
		}

		return 0;
	}


	PicLocation pl = pObj->GetPicLocation();
	int  OBJ_iID	= pl.m_iPicID;
	RECT  OBJ_rect;
	SetRect( &OBJ_rect, pl.m_iLeft, pl.m_iTop, pl.m_iRight, pl.m_iBottom );

	POINT  OBJ_pntPos = pObj->GetPosLT();
	float OBJ_fLayer  = pObj->GetLayer() / 10000.0f;
	float OBJ_fXScale = pObj->GetXScale();
	float OBJ_fYScale = pObj->GetYScale();
	int	  OBJ_fAngle  = pObj->GetAngle();
	DWORD OBJ_dwColor = pObj->GetColorDWORD();

	pCan->GetGraphics()->Draw2D_Advance( OBJ_iID, OBJ_iID, OBJ_pntPos.x, OBJ_pntPos.y, OBJ_fLayer, &OBJ_rect, 
		&OBJ_rect, OBJ_dwColor, 0, OBJ_fAngle, OBJ_fXScale, OBJ_fYScale );


	return 0;
}

/************************************************************************/
/* 动画种类的加入，就像链表结构                                                                    */
/************************************************************************/
bool DrawAnimation::Link( DrawComponent* pDC )
{
	m_pNextComponent = pDC;
	return true;
}

/************************************************************************/
/* xmove                                                                   */
/************************************************************************/
int AnimationMoveX::Draw( Object* pObj, const Canvas* pCan )
{
	if ( pObj->GetBoolGroupByIndex( ANIMATION_TYPE_X_MOVE ) )
	{
		POINT OBJ_pntPos = pObj->GetPosLT();
		int speed = pObj->GetDataGroupByIndex( ANIMATION_PROPERTY_X_SPEED );
		int xend = pObj->GetDataGroupByIndex( ANIMATION_PROPERTY_X_END );

		bool bway = true;
		if ( OBJ_pntPos.x < xend )
		{
			OBJ_pntPos.x += speed;
			bway = true;
		}
		else if ( OBJ_pntPos.x > xend )
		{
			OBJ_pntPos.x -= speed;
			bway = false;
		}

		if ( ( true == bway && OBJ_pntPos.x >= xend )
			||
			( false == bway && OBJ_pntPos.x <= xend ) )
		{
			OBJ_pntPos.x = xend;
			pObj->SetBoolGroupByIndex( ANIMATION_TYPE_X_MOVE, false );
		}

		pObj->SetPosLT( OBJ_pntPos );
	}

	GetNextComponent()->Draw( pObj, pCan );
	return 0;
}

/************************************************************************/
/* AnimationY's                                                                     */
/************************************************************************/
int AnimationMoveY::Draw( Object* pObj, const Canvas* pCan )
{
	if ( pObj->GetBoolGroupByIndex( ANIMATION_TYPE_Y_MOVE ) )
	{
		POINT OBJ_pntPos = pObj->GetPosLT();
		int speed = pObj->GetDataGroupByIndex( ANIMATION_PROPERTY_Y_SPEED );
		int yend = pObj->GetDataGroupByIndex( ANIMATION_PROPERTY_Y_END );

		bool bway = true;
		if ( OBJ_pntPos.y < yend )
		{
			OBJ_pntPos.y += speed;
			bway = true;
		}
		else if ( OBJ_pntPos.y > yend )
		{
			OBJ_pntPos.y -= speed;
			bway = false;
		}

		if ( ( true == bway && OBJ_pntPos.y >= yend )
			||
			( false == bway && OBJ_pntPos.y <= yend ) )
		{
			OBJ_pntPos.y = yend;
			pObj->SetBoolGroupByIndex( ANIMATION_TYPE_Y_MOVE, false );
		}
		pObj->SetPosLT( OBJ_pntPos );
	}

	GetNextComponent()->Draw( pObj, pCan );
	return 0;
}

/************************************************************************/
/* 闪烁动画                                                                     */
/************************************************************************/
int AnimationAlpha::Draw( Object* pObj, const Canvas* pCan )
{
	if ( pObj->GetBoolGroupByIndex( ANIMATION_TYPE_ALPHA ) )
	{
		int alpha_modify = pObj->GetDataGroupByIndex( ANIMATION_PROPERTY_ALPHA );

//		int alpha_value = pObj->GetColorAlpha();
		int alpha_value = pObj->GetColorRed();

		alpha_value += alpha_modify;

		if ( alpha_value > 255 )
		{
			alpha_value = 255;
			pObj->SetDataGroupByIndex( ANIMATION_PROPERTY_ALPHA, -alpha_modify );
		}
		if ( alpha_value < 100 )
		{
			alpha_value = 100;
			pObj->SetDataGroupByIndex( ANIMATION_PROPERTY_ALPHA, -alpha_modify );
		}

		pObj->SetColorRGB( alpha_value, 255, 255 );

	}

	GetNextComponent()->Draw( pObj, pCan );
	return 0;
}

/************************************************************************/
/* 旋转                                                                     */
/************************************************************************/
int AnimationCircumrotate::Draw( Object* pObj, const Canvas* pCan )
{
	if ( pObj->GetBoolGroupByIndex( ANIMATION_TYPE_CIRCUMROTATE ) )
	{
		int rotate = pObj->GetAngle();
		int speed = pObj->GetDataGroupByIndex( ANIMATION_PROPERTY_CIRCUM );

		rotate = ( rotate + speed ) % 360;

		pObj->SetAngle( rotate );
	}


	GetNextComponent()->Draw( pObj, pCan );
	return 0;
}


/************************************************************************/
/* 缩放                                                                     */
/************************************************************************/
int AnimationScale::Draw( Object* pObj, const Canvas* pCan )
{
	if ( pObj->GetBoolGroupByIndex( ANIMATION_TYPE_SCALE ) )
	{
		float scale_x = pObj->GetXScale();
		float scale_y = pObj->GetYScale();
		float speed = pObj->GetDataGroupByIndex( ANIMATION_PROPERTY_SCALE );

		scale_x += speed;
		scale_y += speed;
		if ( scale_x < 0 )
			scale_x = 0;
		if ( scale_y < 0 )
			scale_y = 0;

		pObj->SetXScale( scale_x );
		pObj->SetYScale( scale_y );
	}


	GetNextComponent()->Draw( pObj, pCan );
	return 0;
}

/************************************************************************/
/* 针动画                                                                     */
/************************************************************************/
int AnimationFrame::Draw( Object* pObj, const Canvas* pCan )
{
	if ( pObj->GetBoolGroupByIndex( ANIMATION_TYPE_FRAME ) )
	{
		int curtime = pObj->GetDataGroupByIndex( ANIMATION_PROPERTY_CURTIME );
		int time = pObj->GetDataGroupByIndex( ANIMATION_PROPERTY_TIME );

		curtime++;

		if ( curtime >= time )
		{
			curtime = 0;
			int maxframe = pObj->GetPicLocationSize();
			int curframe = pObj->GetPicLocationCurID();
			int loop = pObj->GetDataGroupByIndex( ANIMATION_PROPERTY_FRAME_LOOP );
			curframe++;
			if ( curframe >= maxframe )
			{
				if ( loop > 0 )
				{
					curframe = 0;
				}
				else
				{
					pObj->SetVisible( false );
				}
			}
			pObj->SetCurPicLocation( curframe );
		}
		pObj->SetDataGroupByIndex( ANIMATION_PROPERTY_CURTIME, curtime );
	}

	GetNextComponent()->Draw( pObj, pCan );
	return 0;
}



