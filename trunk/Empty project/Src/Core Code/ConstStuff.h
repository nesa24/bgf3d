#ifndef CONST_STUFF_H
#define CONST_STUFF_H

namespace ConstStuff
{
const int STRING_LENGTH		= 255; 

//Text const value & Font Setting
const int TEXT_DEFAULT_ROW_WORD_NBR		= 20;
const int TEXT_DEFAULT_Y_OFFSET			= 12;
const int MAX_TEXT_LENGTH				= 100;
const DWORD DEFAULT_TEXT_COLOR			= 0xff000000;
const int DEFAULT_TEXT_ID				= 0;
const int MAXIMUN_RICH_EB_STRING		= 50;
const int MAXIMUN_RICH_EB_STATIC_TEXT	= 10;	

//thie size of bool attributes and number attributes in some objects
const int OBJECT_ATTRIBUTE_SIZE = 20;

//Setting Values
const float LAYER_CONVERT_SIZE	= 0.0001f;
const int LAYER_BOTTOM			= 10000;
const int DEFAULT_OBJECT_LAYER	= 50;
const int DEFAULT_BUTTON_LAYER	= 500;
const int LAYER_SURFACE			= 9000;
const int LAYER_POPUP			= 5000;

const float SCALE_DEFUALT		= 1.0;

}

#endif