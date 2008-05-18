#include "stdafx.h"
#include "DX9Graphics.h"
#include "GraphicsFuns.h"
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

CGameGraphics  *CreateGameGraphics( HWND hwnd, BOOL bWindow, int width, int height )
{
	CGameGraphics *pGraphics;

	pGraphics = new CDX9Graphics;
	
	CHECK( pGraphics->InitGraphics( hwnd, bWindow, width, height ), RIGHT_CREATE );

	return pGraphics;
}

bool ReportError( GraphicsError error )
{
	SYSTEMTIME curtime;
	fstream fout( "ErrorReport.txt", ios::app|ios::out );
	char strreport[MAX_PATH];
	memset( strreport, 0, sizeof(strreport) );

	//获取当前时间
	GetLocalTime( &curtime );

	sprintf( strreport, "Error Report Time: %d:%d:%d", curtime.wHour, curtime.wMinute, curtime.wSecond );

	fout << strreport << endl;

	//写入错误报告文档
	switch ( error )
	{
		case ERR_CREATE_3D:			//创建3D失败
			{
				fout << "错误类型:创建3D对象失败" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_CREATE_MODE:		//设置模式失败
			{
				fout << "错误类型:设置模式失败" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_CREATE_DEVICE:		//创建失败
			{
				fout << "错误类型:创建设备失败" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_VIRTUAL:			//虚函数调用
			{
				fout << "错误类型:调用基类虚函数" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_BEGIN_RENDER:		//开始渲染失败
			{
				fout << "错误类型:BeginRender()失败" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_END_RENDER:		//结束渲染失败
			{
				fout << "错误类型:EndRender()失败" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_DEVICE_VOID:		//设备失效
			{
				fout << "错误类型:设备尚未创建或已经释放" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_SPRITE_VOID:		//精灵对象为空
			{
				fout << "错误类型:精灵尚未创建或已经释放" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_TEXTURE_VOID:		//资源为空
			{
				fout << "错误类型:图像资源尚未创建或已经释放" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_FONT_VOID:			//字体为空
			{
				fout << "错误类型:字体资源尚未创建或已经释放" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_FILL_SURFACE:		//页面添色失败
			{
				fout << "错误类型:页面填充颜色失败" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_SETUP_MATRICES:	//设置视角失败
			{
				fout << "错误类型:视角设定失败" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_PRESENT:			//翻转页面失败
			{
				fout << "错误类型:翻页失败" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_SET_LIGHTING:		//设置光线失败
			{
				fout << "错误类型:设置灯光失败" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_SET_CULL:			//设置三角形绘制方法失败
			{
				fout << "错误类型:设置渲染三角形顺序失败" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_SET_ZBUFFER:		//设置Z-BUFFER失败
			{
				fout << "错误类型:设置Z-BUFFER失败" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_CREATE_FONT:		//创建字体失败
			{
				fout << "错误类型:创建字体失败" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_CREATE_SURFACE:	//创建页面失败
			{
				fout << "错误类型:创建页面失败" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_CREATE_SPRITE:		//创建精灵失败
			{
				fout << "错误类型:创建精灵失败" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_LOAD_PIC:			//加载图像资源失败
			{
				fout << "错误类型:加载图像资源失败" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_BEGIN_SPRITE:		//开始渲染精灵失败
			{
				fout << "错误类型:BeginSprite()失败" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_END_SPRITE:		//结束渲染精灵失败
			{
				fout << "错误类型:EndSprite()失败" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_SET_WORLD_POS:		//设置世界坐标失败
			{
				fout << "错误类型:设置世界坐标失败" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_DRAW_ADVANCE:		//绘制函数调用失败
			{
				fout << "错误类型:Draw_Advance()失败" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_DRAW_ALPHA:		//绘制函数调用失败
			{
				fout << "错误类型:Draw_Alpha()失败" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_DRAW_BASE:			//绘制函数调用失败
			{
				fout << "错误类型:Draw_Base()失败" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_NUMBER_OVER:		//数字溢出
			{
				fout << "错误类型:数值溢出" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_MEM_NEW:			//分配资源失败
			{
				fout << "错误类型:动态分配内存失败" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_DRAW_TEXT:			//绘制文字失败
			{
				fout << "错误类型:绘制文字失败" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_MEMORY_NULL:		//指定内存为空
			{
				fout << "错误类型:指定内存为空" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_LOAD_FROM_MEM:		//从内存加载资源失败
			{
				fout << "错误类型:从内存加载资源失败" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_CREATE_OFF_SURFACE:	//创建动态离屏页面失败
			{
				fout << "错误类型:创建动态离屏页面失败" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_GET_BACK_BUFFER:	//获取后台页面失败
			{
				fout << "错误类型:获取后台页面失败" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_SAVE_SURFACE:		//保存页面失败
			{
				fout << "错误类型:保存页面失败" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_LOCK_SURFACE:		//锁页面失败
			{
				fout << "错误类型:锁页面失败" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		default:					//其他
			{
				fout << "未知错误" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
	}
	return true;
}