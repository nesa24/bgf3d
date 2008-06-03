
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the GAMEGRAPHICS_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// GAMEGRAPHICS_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef GAMEGRAPHICS_EXPORTS
#define GAMEGRAPHICS_API __declspec(dllexport)
#else
#define GAMEGRAPHICS_API __declspec(dllimport)
#endif

#include "GrahicsErr.h"
#ifndef GAMEGRAPHICS_H
#define GAMEGRAPHICS_H

//3D primitive vertex
struct CustomVertex3D
{
	float x,y,z;
	DWORD color;
};

//3D rhw primitive vertex
struct CustomVertex2D
{
	float x,y,z, rhw;
	DWORD color;
};

enum ShapeType
{
	ShapePoint = 0,
	ShapeLine,
	ShapeTriangleStrip,

	//shape number
	ShapeNbr
};

// This class is exported from the GameGraphics.dll
class GAMEGRAPHICS_API CGameGraphics {
public:
	//释放目标页面资源
	//参数:页面的ID
	//会释放资源占用的内存
	virtual GraphicsError ReleaseSurface( int iID );
	//绘制文字
	//参数:字体ID,坐标x,y,文字指针,颜色,换行长度(像素),字符间隔(像素),字符行距(像素)
	virtual GraphicsError PrintText(int iID, int x, int y, char *text, DWORD color, int iwidth = 60, int isize_x = 12, int isize_y = 20);
	//关闭精灵
	//和打开精灵相对应,在使用精灵之后必须调用
	virtual GraphicsError EndSprite();
	//打开精灵
	//和关闭精灵相对应,在使用精灵之前必须调用
	virtual GraphicsError BeginSprite();
	//绘制图象
	//参数:目标页面ID,源页面ID,坐标x,y,页面所在层数,源页面矩形
	//没有比例,颜色,形状上面的附加操作
	virtual GraphicsError Draw2D_Base(int iDescID, int iSrcID, int x, int y, float z = 1.0f, LPRECT lpSrcRect = NULL );
	//绘制图象
	//参数:目标页面ID,源页面ID,坐标x,y,页面所在层数,目标页面矩形,源页面矩形,颜色值,透明度值(目前没有用)透明值包含在前面的颜色值中
	//没有比例,形状上面的附加操作,多加了对颜色的操作接口,但执行速度和前一个是一样的
	virtual GraphicsError Draw2D_Alpha(int iDescID, int iSrcID, int x, int y, float z = 1.0f, LPRECT lpdesc_rect = NULL, LPRECT lpsrc_rect = NULL, DWORD color = 0xffffffff, int alpha = 0);
	//绘制图象
	//参数:目标页面ID,源页面ID,坐标x,y,页面所在层数,目标页面矩形,源页面矩形,颜色值,透明度值(目前没有用)透明值包含在前面的颜色值中,
	//旋转角度,X轴缩放比例,Y轴缩放比例
	//基本满足2D图象的操作,包括了对旋转,缩放的操作,但因为会造成世界坐标的修改,所以内包含了独自的精灵操作
	//速度有影响,不如前面的函数快
	virtual GraphicsError Draw2D_Advance(int iDescID, int iSrcID, int x, int y, float z = 1.0f, LPRECT lpdesc_rect = NULL, LPRECT lpsrc_rect = NULL, DWORD color = 0xffffffff, int alpha = 0, int angle = 0, float size_x = 1.0f, float size_y = 1.0f);
	//载入资源图片
	//参数:页面ID,资源文件名
	//资源图片尺寸必须满足2,4,8,16,32,64,128,256,512,1024,最好不要超过1024,因为图象资源太大,会严重影响图象绘制效率
	//如果不满足条件,硬件会自动缩放到规定尺寸
	virtual GraphicsError LoadPic( int iID, char* filename );
	//创建页面
	//参数:页面的尺寸宽,高
	//现在参数没有实际意义,页面固定成了资源图片的尺寸
	virtual GraphicsError CreateSurface( int width, int height );
	//创建字体
	//参数:字体码数,字体类型(比如:"宋体"),是否粗体,是否斜体
	virtual GraphicsError DXCreateFont( int iSize, char *strType, BOOL bBold = FALSE, BOOL bSharp = FALSE );
	//初始化设置渲染属性等
	virtual GraphicsError InitGeometry();
	//渲染函数,每次要调用此函数才能完成整个渲染
	virtual GraphicsError Render();
	//填充页面
	//参数:页面ID,颜色
	virtual GraphicsError FillSurface( int iID, DWORD color );
	//填充页面指定区域
	//参数:页面ID,颜色,区域
	virtual GraphicsError FillSurfaceRect( int iID, DWORD color, LPRECT lpR = NULL );
	//关闭渲染操作
	//和开始渲染操作相对应,必须成对出现
	virtual GraphicsError EndRender();
	//开始渲染操作
	//和关闭渲染操作相对应,必须成对出现
	virtual GraphicsError BeginRender();
	//释放所有资源
	virtual GraphicsError ShutGraphics();
	//设置视角和世界坐标
	virtual GraphicsError SetupMatrices();
	//初始化设备
	//参数:窗口句柄,是否全屏,全屏时的尺寸
	virtual GraphicsError InitGraphics( HWND hwnd, BOOL bWindow = TRUE, int width = 800, int height = 600 );
	//载入页面资源从内存中载入
	//参数:页面ID,页面资源指针,资源长度
	virtual GraphicsError LoadPicFromFileInMemory(int iID, LPCVOID pSrcData, UINT SrcDataSize);
	//释放目标页面资源
	//参数:页面的ID
	//会释放资源占用的内存
	virtual GraphicsError ReleasePicSurface( int iID );
	//记录当前显示页面到文件中
	//参数:记录文件名,文件类型,保存页面的范围
	virtual GraphicsError SaveSurfaceToFile( char* filename, const int SaveType = SAVE_TYPE_JPG, LPRECT lpSrcRect = NULL );
	//锁住页面
	//参数:目标ID,范围(NULL为全部),返回首指针,返回单行长度
	virtual GraphicsError LockSurface( const int iID, LPRECT lprect, BYTE* &pByte, int &pitch );
	//解锁页面
	//参数:目标ID
	virtual GraphicsError UnlockSurface( const int iID );

	CGameGraphics(void);

	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//ly's added
	virtual GraphicsError Draw2DShape( ShapeType theType, void* pVertexBuffer, int iPrimitiveNumber );
	virtual GraphicsError Draw3DShape( ShapeType theType, void* pVertexBuffer, int iPrimitiveNumber, float* fRotate );
	virtual GraphicsError CreateVertexBuffer( void** ppBuffer, int iBufferSize, bool b2DBuffer);
	virtual GraphicsError UpdateVertexBuffer( void* pVertex, void* pBuffer, size_t Size );
	virtual void ReleaseVertexBuffer( void* pBuffer ) = 0;
	//ly's adde end
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	

};

class GAMEGRAPHICS_API CDX9Graphics;

#endif


