#ifndef GRAPHICSERR_H
#define GRAPHICSERR_H

enum GraphicsError
{
	ERR_CREATE_3D = 0,		//创建3D失败
	ERR_CREATE_MODE,		//设置模式失败
	ERR_CREATE_DEVICE,		//创建失败
	ERR_VIRTUAL,			//虚函数调用
	ERR_BEGIN_RENDER,		//开始渲染失败
	ERR_END_RENDER,			//结束渲染失败
	ERR_DEVICE_VOID,		//设备失效
	ERR_SPRITE_VOID,		//精灵对象为空
	ERR_TEXTURE_VOID,		//资源为空
	ERR_FONT_VOID,			//字体为空
	ERR_FILL_SURFACE,		//页面添色失败
	ERR_SETUP_MATRICES,		//设置视角失败
	ERR_PRESENT,			//翻转页面失败
	ERR_SET_LIGHTING,		//设置光线失败
	ERR_SET_CULL,			//设置三角形绘制方法失败
	ERR_SET_ZBUFFER,		//设置Z-BUFFER失败
	ERR_CREATE_FONT,		//创建字体失败
	ERR_CREATE_SURFACE,		//创建页面失败
	ERR_CREATE_SPRITE,		//创建精灵失败
	ERR_LOAD_PIC,			//加载图像资源失败
	ERR_BEGIN_SPRITE,		//开始渲染精灵失败
	ERR_END_SPRITE,			//结束渲染精灵失败
	ERR_SET_WORLD_POS,		//设置世界坐标失败
	ERR_DRAW_ADVANCE,		//绘制函数调用失败
	ERR_DRAW_ALPHA,			//绘制函数调用失败
	ERR_DRAW_BASE,			//绘制函数调用失败
	ERR_NUMBER_OVER,		//数字溢出
	ERR_MEM_NEW,			//分配资源失败
	ERR_DRAW_TEXT,			//绘制文字失败
	ERR_MEMORY_NULL,		//指定内存为空
	ERR_LOAD_FROM_MEM,		//从内存加载资源失败
	ERR_CREATE_OFF_SURFACE,	//创建动态离屏页面失败
	ERR_GET_BACK_BUFFER,	//获取后台页面失败
	ERR_SAVE_SURFACE,		//保存页面失败
	ERR_LOCK_SURFACE,		//锁页面失败

	RIGHT_CREATE,			//创建成功
	RIGHT_RELEASE,			//释放资源成功
	RIGHT_BEGIN_RENDER,		//开始渲染成功
	RIGHT_END_RENDER,		//结束渲染成功
	RIGHT_FILL_SURFACE,		//页面添色成功
	RIGHT_SETUP_MATRICES,	//设置视角成功
	RIGHT_PRESENT,			//翻转页面成功
	RIGHT_SET_STATE,		//设置状态成功
	RIGHT_CREATE_FONT,		//创建字体成功
	RIGHT_CREATE_SURFACE,	//创建页面成功
	RIGHT_LOAD_PIC,			//加载图像资源成功
	RIGHT_DRAW_ADVANCE,		//绘制成功
	RIGHT_DRAW_ALPHA,		//绘制成功
	RIGHT_DRAW_BASE,		//绘制成功
	RIGHT_BEGIN_SPRITE,		//开始渲染精灵成功
	RIGHT_END_SPRITE,		//结束渲染精灵成功
	RIGHT_DRAW_TEXT,		//绘制文字成功
	RIGHT_LOAD_FROM_MEM,	//从内存加载资源成功
	RIGHT_RELEASE_SURFACE,	//释放资源成功
	RIGHT_SAVE_SURFACE,		//保存页面成功
	RIGHT_LOCK_SURFACE,		//锁页面成功
	RIGHT_UNLOCK_SURFACE,	//解锁页面成功

	//ly's added flag
	ERR_D3D_SHAPE,			//D3D作图失败
	ERR_CREATE_BUFFER,		//创建定点buffer失败
	ERR_LOCK_BUFFER,		//锁定定点buffer失败
	ERR_D3D_CAMERA,			//Camera setting error

	RIGHT_D3D_SHAPE,		
	RIGHT_CREATE_BUFFER,
	RIGHT_LOCK_BUFFER,
	RIGHT_D3D_CAMERA,
	//ly's added end

	ERR_NO
};

//save file type
const int SAVE_TYPE_JPG = 0;
const int SAVE_TYPE_PNG = 1;
const int SAVE_TYPE_BMP = 2;

extern char g_strError_Report_Buffer[MAX_PATH];

#define _DEBUG_GRAPHICS

#ifdef _DEBUG_GRAPHICS
#define CHECK( LINE, C ) { GraphicsError res = LINE; if ( res != C ) ReportError( res ); }
#else
#define CHECK( LINE, C ) LINE
#endif
  
#endif