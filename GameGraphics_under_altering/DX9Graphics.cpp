// DX9Graphics.cpp: implementation of the CDX9Graphics class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DX9Graphics.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDX9Graphics::CDX9Graphics()
{
	m_hWnd = NULL;
	m_lpD3d = NULL;
	m_lpDev = NULL;
	m_lppFont.clear();
	m_lppTex.clear();
}

CDX9Graphics::~CDX9Graphics()
{
}

GraphicsError CDX9Graphics::InitGraphics( HWND hwnd, BOOL bWindow, int width, int height )
{
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;
	HRESULT hres = 0;

	m_hWnd = hwnd;

	m_lpD3d = Direct3DCreate9(D3D_SDK_VERSION);
	
	if (m_lpD3d == NULL)
	{
		MessageBox( NULL, "创建D3D句柄失败", NULL, MB_OK);

		//Write Error Report
		sprintf( g_strError_Report_Buffer, "Direct3DCreate9(D3D_SDK_VERSION) HWND: %d, bWindow: %d", (int)hwnd, (int)bWindow );
		//
		return ERR_CREATE_3D;
	}
	
	if (FAILED( hres = m_lpD3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm )))
	{
		MessageBox( NULL, "获得显示模式失败", NULL, MB_OK);

		//Write Error Report
		sprintf( g_strError_Report_Buffer, "m_lpD3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm) hres:%d", hres );
		//

		return ERR_CREATE_MODE;
	}
	
	//清空d3dpp
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	
	if (bWindow == TRUE)
	{
		//窗口版
		d3dpp.Windowed = TRUE;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
		d3dpp.PresentationInterval   = D3DPRESENT_INTERVAL_IMMEDIATE;
	}
	else
	{
		d3dpp.BackBufferWidth = width;
		d3dpp.BackBufferHeight = height;
		d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;	//32位显示
		d3dpp.BackBufferCount = 1;
		d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
		d3dpp.MultiSampleQuality = 0;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.hDeviceWindow = hwnd;
		d3dpp.Windowed = FALSE;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
		d3dpp.Flags = 0;
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	}
	
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;	//生成16 bit的Z缓存
	
	if (FAILED(hres = m_lpD3d->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hwnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_lpDev)))
	{
		if ( FAILED(hres = m_lpD3d->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL, 
			hwnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&m_lpDev)))
		{
			if ( FAILED(hres = m_lpD3d->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_REF, 
			hwnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&m_lpDev)))
			{
				MessageBox( NULL, "创建D3D设备失败", NULL, MB_OK);

				//Write Error Report
				string resreport;
				switch( hres )
				{
				case D3DERR_DEVICELOST:
					resreport = "设备丢失";
					break;
				case D3DERR_INVALIDCALL:
					resreport = "参数错误";
					break;
				case D3DERR_NOTAVAILABLE:
					resreport = "设备不支持";
					break;
				case D3DERR_OUTOFVIDEOMEMORY:
					resreport = "显存不足";
					break;
				default:
					resreport = "其他内型错误";
				}

				sprintf( g_strError_Report_Buffer, "m_lpD3d->CreateDevice() hres: %s", resreport.c_str() );
				//

				return ERR_CREATE_DEVICE;
			}
		}
	}

	return RIGHT_CREATE;
}

GraphicsError CDX9Graphics::ShutGraphics()
{
	int i = 0;
	for ( i =  m_lppFont.size() - 1; i >=0; --i )
	{
		SAFE_RELEASE( m_lppFont[i] );
	}

	SAFE_RELEASE( m_lpSpr );
	
	for ( i = m_lppTex.size() - 1; i >= 0; --i )
	{		 
		SAFE_RELEASE( m_lppTex[i] );
	}

	SAFE_RELEASE( m_lpDev );
	SAFE_RELEASE( m_lpD3d );

	return RIGHT_RELEASE;
}

GraphicsError CDX9Graphics::BeginRender()
{
	HRESULT hres = 0;

	if ( m_lpDev )
	{
		if ( FAILED( hres = m_lpDev->BeginScene() ) )
		{
			//Write Error Report
			sprintf( g_strError_Report_Buffer, "m_lpDev->BeginScene() hres:%d", hres );
			//

			return ERR_BEGIN_RENDER;
		}
		else
			return RIGHT_BEGIN_RENDER;
	}

	//Write Error Report
	sprintf( g_strError_Report_Buffer, "BeginRender() m_lpDev:%d", (int)m_lpDev );
	//

	return ERR_DEVICE_VOID;
}

GraphicsError CDX9Graphics::EndRender()
{
	HRESULT hres = 0;

	if ( m_lpDev )
	{
		if ( FAILED(m_lpDev->EndScene() ) )
		{
			//Write Error Report
			sprintf( g_strError_Report_Buffer, "m_lpDev->EndScene() hres:%d", hres );
			//
			return ERR_END_RENDER;
		}
		else
			return RIGHT_END_RENDER;
	}

	//Write Error Report
	sprintf( g_strError_Report_Buffer, "EndRender() m_lpDev:%d", (int)m_lpDev );
	//
	return ERR_DEVICE_VOID;
}

GraphicsError CDX9Graphics::FillSurface(int iID, DWORD color)
{
	HRESULT hres = 0;

	//调用Clear函数填充设定颜色
	if ( m_lpDev )
	{
		if ( FAILED( hres = m_lpDev->Clear(
			0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
			color,
			1.0f, 0) ) )
		{
			//Write Error Report
			sprintf( g_strError_Report_Buffer, "m_lpDev->Clear() hres:%d", hres );
			//
			return ERR_FILL_SURFACE;
		}
		else
			return RIGHT_FILL_SURFACE;
	}

	//Write Error Report
	sprintf( g_strError_Report_Buffer, "FillSurface() m_lpDev:%d", (int)m_lpDev );
	//
	return ERR_DEVICE_VOID;
}

GraphicsError CDX9Graphics::FillSurfaceRect( int iID, DWORD color, LPRECT lpR )
{
	HRESULT hres = 0;

	if ( m_lpDev )
	{
		if ( lpR )
		{
			D3DRECT prect;
			prect.x1 = lpR->left;
			prect.x2 = lpR->right;
			prect.y1 = lpR->top;
			prect.y2 = lpR->bottom;
			if ( FAILED( hres = m_lpDev->Clear(
				1, &prect, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
				color,
				1.0f, 0 ) ) )
			{
				//Write Error Report
				sprintf( g_strError_Report_Buffer, "m_lpDev->Clear() hres:%d, prect.x1:%d, prect.x2:%d, prect.y1:%d, prect.y2:%d",
					hres, prect.x1, prect.x2, prect.y1, prect.y2 );
				//
				return ERR_FILL_SURFACE;
			}
			else
				return RIGHT_FILL_SURFACE;
		}
		else
		{
			GraphicsError res = ERR_NO;
			CHECK( res = FillSurface(iID, color), RIGHT_FILL_SURFACE );
			return res;
		}	
	}

	//Write Error Report
	sprintf( g_strError_Report_Buffer, "FillSurfaceRect() m_lpDev:%d", (int)m_lpDev );
	//
	return ERR_DEVICE_VOID;

}

GraphicsError CDX9Graphics::SetupMatrices()
{
	HRESULT hres = 0;

	D3DXVECTOR3 eye( 0.0f, 3.0f, -5.0f );	//观察点
	D3DXVECTOR3 lookat( 0.0f, 0.0f, 0.0f );	//视线目标点
	D3DXVECTOR3 up( 0.0f, 1.0f, 0.0f );		//上方向
	D3DXMATRIX matView;
	//计算视角变换矩阵
	D3DXMatrixLookAtLH( &matView, &eye, &lookat, &up );

	if ( m_lpDev )
	{
		//把视角变换矩阵设置到渲染环境
		if ( FAILED( hres = m_lpDev->SetTransform( D3DTS_VIEW, &matView ) ) )
		{
			//Write Error Report
			sprintf( g_strError_Report_Buffer, "m_lpDev->SetTransform() hres:%d", (int)hres );
			//
			return ERR_SETUP_MATRICES;
		}
		else
			return RIGHT_SETUP_MATRICES;
	}

	//Write Error Report
	sprintf( g_strError_Report_Buffer, "SetupMatrices() m_lpDev:%d", (int)m_lpDev );
	//
	return ERR_DEVICE_VOID;
}

GraphicsError CDX9Graphics::Render()
{
	HRESULT hres = 0;

	if ( m_lpDev )
	{
		if ( FAILED( hres = m_lpDev->Present( NULL, NULL, NULL, NULL ) ) )
		{
			//Write Error Report
			sprintf( g_strError_Report_Buffer, "m_lpDev->Present() hres:%d", (int)hres );
			//
			return ERR_PRESENT;
		}
		else
		{
			if ( D3DERR_DEVICELOST == m_lpDev->TestCooperativeLevel() )
				MessageBox( NULL, "设备丢失!", NULL, MB_OK );
			
			return RIGHT_PRESENT;
		}
	}

	//Write Error Report
	sprintf( g_strError_Report_Buffer, "Render() m_lpDev:%d", (int)m_lpDev );
	//
	return ERR_DEVICE_VOID;
}

GraphicsError CDX9Graphics::InitGeometry()
{
	HRESULT hres = 0;
	if ( m_lpDev )
	{
		//初始化摄像头和世界坐标
		InitMatrix();

		//打开定点半透明效果
		//set alpha
		m_lpDev->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		// set alpha blend for source cone
		m_lpDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		// set alpha blend for dest cone
		m_lpDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		//set back face culling
		m_lpDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_FORCE_DWORD);


		//不使用光照处理
		if ( FAILED( hres = m_lpDev->SetRenderState( D3DRS_LIGHTING, FALSE ) ) )
		{
			//Write Error Report
			sprintf( g_strError_Report_Buffer, "m_lpDev->SetRenderState(D3DRS_LIGHTING) hres:%d", hres );
			//
			return ERR_SET_LIGHTING;
		}

//		//正逆三角形绘画
//		if ( FAILED( hres = m_lpDev->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE ) ) )
//		{
//			//Write Error Report
//			sprintf( g_strError_Report_Buffer, "m_lpDev->SetRenderState(D3DRS_CULLMODE) hres:%d", hres );
//			//
//			return ERR_SET_CULL;
//		}

		m_lpDev->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_NONE );
		m_lpDev->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_POINT );
		m_lpDev->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_POINT );

		//打开Z_buffer
		if ( FAILED( hres = m_lpDev->SetRenderState( D3DRS_ZENABLE, D3DZB_TRUE ) ) )
		{
			//Write Error Report
			sprintf( g_strError_Report_Buffer, "m_lpDev->SetRenderState(D3DRS_ZENABLE) hres:%d", hres );
			//
			return ERR_SET_ZBUFFER;
		}

		return RIGHT_SET_STATE;
	}

	//Write Error Report
	sprintf( g_strError_Report_Buffer, "InitGeometry() m_lpDev:%d", (int)m_lpDev );
	//

	return ERR_DEVICE_VOID;
}

GraphicsError CDX9Graphics::DXCreateFont( int iSize, char *strType, BOOL bBold, BOOL bSharp )
{
	if ( NULL == m_lpDev )
	{
		//Write Error Report
		sprintf( g_strError_Report_Buffer, "DXCreateFont() m_lpDev:%d", (int)m_lpDev );
		//
		return ERR_DEVICE_VOID;
	}

	LPD3DXFONT lpFont;
	HRESULT hresult;

	if ( bBold )
		hresult = D3DXCreateFont( m_lpDev, iSize, 0, FW_BOLD, 0, bSharp, GB2312_CHARSET, 0, 0, 0, strType, &lpFont );
	else
		hresult = D3DXCreateFont( m_lpDev, iSize, 0, 0, 0, bSharp, GB2312_CHARSET, 0, 0, 0, strType, &lpFont );
		
	if ( hresult == D3D_OK )
		m_lppFont.push_back( lpFont );
	else
	{
		char result[32];
		sprintf( result, "创建%s字体失败", strType );
		//Write Error Report
		sprintf( g_strError_Report_Buffer, "DXCreateFont() hresult:%d, Font:%s", hresult, strType );
		//

		MessageBox( NULL, result, NULL, MB_OK );
		return ERR_CREATE_FONT;
	}

	return RIGHT_CREATE_FONT;
}

GraphicsError CDX9Graphics::CreateSurface(int width, int height)
{
	LPDIRECT3DTEXTURE9 lpTex;

	HRESULT hres;
	if ( m_lpDev )
	{
		if ( FAILED( hres = D3DXCreateSprite( m_lpDev, &m_lpSpr ) )  )
		{
			//Write Error Report
			sprintf( g_strError_Report_Buffer, "D3DXCreateSprite() hres:%d", hres );
			//
			return ERR_CREATE_SPRITE;
		}
	}
	else
	{
		//Write Error Report
		sprintf( g_strError_Report_Buffer, "CreateSurface() m_lpDev:%d", (int)m_lpDev );
		//
		return ERR_DEVICE_VOID;
	}

	if ( D3D_OK == hres )
	{
		m_lppTex.push_back( lpTex );
		return RIGHT_CREATE_SURFACE;
	}
	else
	{
		//Write Error Report
		sprintf( g_strError_Report_Buffer, "CreateSurface() hres:%d", hres );
		//
		return ERR_CREATE_SURFACE;
	}
}

GraphicsError CDX9Graphics::LoadPic(int iID, char *filename)
{
	if ( NULL == m_lpDev )
	{
		//Write Error Report
		sprintf( g_strError_Report_Buffer, "LoadPic() m_lpDev:%d", (int)m_lpDev );
		//
		return ERR_DEVICE_VOID;
	}

	HRESULT hres = D3DXCreateTextureFromFileEx(
					m_lpDev, 
					filename,			//文件名
					D3DX_DEFAULT,		//文件宽，这里设为自动
					D3DX_DEFAULT,		//文件高，这里设为自动
					D3DX_DEFAULT,		//需要多少级mipmap，这里设为自动
					0,					//此纹理的用途
					D3DFMT_UNKNOWN,		//自动检测文件格式
					//D3DFMT_DXT1,
					D3DPOOL_DEFAULT,    //交由graphics管理
					//D3DX_DEFAULT,
					//D3DX_DEFAULT, 
					D3DX_FILTER_NONE,	//纹理过滤方法，不使用任何方法
					D3DX_FILTER_NONE,	//mipmap纹理过滤方法，不使用任何方法
					0xffff00ff,			//KeyColor
					NULL,				//读出的图像格式存储在何变量中
					NULL,				//读出的调色板存储在何变量中
					&m_lppTex[iID]);	//要创建的纹理

	//m_lpDev->EvictManagedResources();
	
	if ( D3D_OK == hres )
		return RIGHT_LOAD_PIC;
	else
	{
		//交给D3DGraphics管理
		hres = D3DXCreateTextureFromFileEx(
						m_lpDev, 
						filename,			//文件名
						D3DX_DEFAULT,		//文件宽，这里设为自动
						D3DX_DEFAULT,		//文件高，这里设为自动
						D3DX_DEFAULT,		//需要多少级mipmap，这里设为自动
						0,					//此纹理的用途
						D3DFMT_DXT1,		//DXT1压缩
						D3DPOOL_MANAGED,    //由DXGraphics管理
						//D3DX_DEFAULT,
						//D3DX_DEFAULT,
						D3DX_FILTER_NONE,	//纹理过滤方法，不使用任何方法
						D3DX_FILTER_NONE,	//mipmap纹理过滤方法，不使用任何方法
						0xffff00ff,			//KeyColor
						NULL,				//读出的图像格式存储在何变量中
						NULL,				//读出的调色板存储在何变量中
						&m_lppTex[iID]);	//要创建的纹理

		if ( D3D_OK == hres )
			return RIGHT_LOAD_PIC;		

		hres = D3DXCreateTextureFromFileEx(
						m_lpDev, 
						filename,			//文件名
						D3DX_DEFAULT,		//文件宽，这里设为自动
						D3DX_DEFAULT,		//文件高，这里设为自动
						D3DX_DEFAULT,		//需要多少级mipmap，这里设为自动
						0,					//此纹理的用途
						D3DFMT_UNKNOWN,		//自动检测文件格式
						D3DPOOL_MANAGED,    //由DXGraphics管理
						//D3DX_DEFAULT,
						//D3DX_DEFAULT,
						D3DX_FILTER_NONE,	//纹理过滤方法，不使用任何方法
						D3DX_FILTER_NONE,	//mipmap纹理过滤方法，不使用任何方法
						0xffff00ff,			//KeyColor
						NULL,				//读出的图像格式存储在何变量中
						NULL,				//读出的调色板存储在何变量中
						&m_lppTex[iID]);	//要创建的纹理

		MessageBox( NULL, "加载图像资源出错", NULL, MB_OK );
		//Write Error Report
		string errreport;

		switch ( hres )
		{
		case D3DERR_INVALIDCALL:
			errreport = "参数错误 错误内型:D3DERR_INVALIDCALL";
			break;
		case D3DERR_NOTAVAILABLE:
			errreport = "设备不支持";
			break;
		case D3DERR_OUTOFVIDEOMEMORY:
			errreport = "显存不足";
			break;
		case D3DXERR_INVALIDDATA:
			errreport = "参数错误 错误内型:D3DXERR_INVALIDDATA";
			break;
		case E_OUTOFMEMORY:
			errreport = "内存不足";
			break;
		default:
			errreport = "其他错误结果";
			break;
		}
		sprintf( g_strError_Report_Buffer, "D3DXCreateTextureFromFileEx() hres:%s, file id:%d, file name:%s", errreport.c_str(), iID, filename );
		//
		return ERR_LOAD_PIC;
	}
}

GraphicsError CDX9Graphics::Draw2D_Advance(int iDescID, int iSrcID, int x, int y, float z, LPRECT lpdesc_rect, LPRECT lpsrc_rect, DWORD color, int alpha, int angle, float size_x, float size_y)
{
	HRESULT hres = 0;

	if ( NULL == m_lpSpr )
	{
		//Write Error Report
		sprintf( g_strError_Report_Buffer, "Draw2D_Advance() m_lpSpr:%d", (int)m_lpSpr );
		//
		return ERR_SPRITE_VOID;
	}

	if ( NULL == m_lpDev )
	{
		//Write Error Report
		sprintf( g_strError_Report_Buffer, "Draw2D_Advance() m_lpDev:%d", (int)m_lpDev );
		//
		return ERR_DEVICE_VOID;
	}

	if ( iSrcID < 0 || iSrcID >= m_lppTex.size() )
	{
		//Write Error Report
		sprintf( g_strError_Report_Buffer, "Draw2D_Advance() iSrcID < 0 || iSrcID >= m_lppTex.size() iSrcID:%d, m_lppTex.size():%d", iSrcID, m_lppTex.size() );
		//
		return ERR_NUMBER_OVER;
	}

	if ( NULL == m_lppTex[iSrcID] )
	{
		//Write Error Report
		sprintf( g_strError_Report_Buffer, "Draw2D_Advance() m_lppTex[iSrcID]:%d", (int)m_lppTex[iSrcID] );
		//
		return ERR_TEXTURE_VOID;
	}

	if ( FAILED( hres = m_lpSpr->Begin( D3DXSPRITE_ALPHABLEND ) ) )
	{
		//Write Error Report
		sprintf( g_strError_Report_Buffer, "Draw2D_Advance()  m_lpSpr->Begin() hres:%d", hres );
		//
		return ERR_BEGIN_SPRITE;
	}

	D3DXMATRIX matw,mato,matt;
	
	if ( FAILED( hres = m_lpDev->GetTransform( D3DTS_WORLD, &matw ) ) )
	{
		//Write Error Report
		sprintf( g_strError_Report_Buffer, "Draw2D_Advance() m_lpDev->GetTransform() hres:%d", hres );
		//
		return ERR_SET_WORLD_POS;
	}

	mato = matw;
	
	int pos_x = x;
	int pos_y = y;

	if ( angle != 0 )
	{
		float a = ( -angle * D3DX_PI ) / 180.0f;
		//计算中心距离
		float width = ( lpsrc_rect->right - lpsrc_rect->left ) / 2.0f;
		float height = ( lpsrc_rect->bottom - lpsrc_rect->top ) / 2.0f;

		D3DXMatrixTranslation( &matt, -width, -height, z );
		D3DXMatrixMultiply( &matw, &matw, &matt );

		pos_x += width;
		pos_y += height;

		//旋转
		D3DXMatrixRotationYawPitchRoll( &matt, 0.0f, 0.0f, a );
		D3DXMatrixMultiply( &matw, &matw, &matt );
	}
	
	//缩放
	D3DXMatrixScaling( &matt, size_x, size_y, 0.0f );
	D3DXMatrixMultiply( &matw, &matw, &matt );
	//移动
	D3DXMatrixTranslation( &matt, pos_x, pos_y, z );
	D3DXMatrixMultiply( &matw, &matw, &matt );
	
	if ( FAILED( hres = m_lpDev->SetTransform( D3DTS_WORLD, &matw ) ) )
	{
		//Write Error Report
		sprintf( g_strError_Report_Buffer, "Draw2D_Advance() m_lpDev->GetTransform() hres:%d", hres );
		//
		return ERR_SET_WORLD_POS;
	}
	
	D3DXVECTOR3 vCenter( 0.0f, 0.0f, 0.0f );	
	D3DXVECTOR3 vPosition( 0, 0, z );
	
	
    if ( FAILED( hres = m_lpSpr->Draw( m_lppTex[iSrcID],
		lpsrc_rect,
		&vCenter,
		&vPosition,
		color ) ) )
	{
		//Write Error Report
		sprintf( g_strError_Report_Buffer, "Draw2D_Advance() m_lpSpr->Draw() hres:%d", hres );
		//
		return ERR_DRAW_ADVANCE;
	}
	
	if ( FAILED( hres = m_lpSpr->End() ) )
	{
		//Write Error Report
		sprintf( g_strError_Report_Buffer, "Draw2D_Advance() m_lpSpr->End() hres:%d", hres );
		//
		return ERR_END_SPRITE;
	}

	if ( FAILED( m_lpDev->SetTransform( D3DTS_WORLD, &mato ) ) )
	{
		//Write Error Report
		sprintf( g_strError_Report_Buffer, "Draw2D_Advance() m_lpDev->GetTransform() hres:%d", hres );
		//
		return ERR_SET_WORLD_POS;
	}

	return RIGHT_DRAW_ADVANCE;
}

GraphicsError CDX9Graphics::Draw2D_Alpha(int iDescID, int iSrcID, int x, int y, float z, LPRECT lpdesc_rect, LPRECT lpsrc_rect, DWORD color, int alpha)
{
	HRESULT hres = 0;

	if ( NULL == m_lpSpr )
	{
		//Write Error Report
		sprintf( g_strError_Report_Buffer, "Draw2D_Alpha() m_lpSpr:%d", (int)m_lpSpr );
		//
		return ERR_SPRITE_VOID;
	}

	if ( iSrcID < 0 || iSrcID >= m_lppTex.size() )
	{
		//Write Error Report
		sprintf( g_strError_Report_Buffer, "Draw2D_Alpha() iSrcID < 0 || iSrcID >= m_lppTex.size() iSrcID:%d, m_lppTex.size():%d", iSrcID, m_lppTex.size() );
		//
		return ERR_NUMBER_OVER;
	}

	if ( NULL == m_lppTex[iSrcID] )
	{
		//Write Error Report
		sprintf( g_strError_Report_Buffer, "Draw2D_Alpha() m_lppTex[iSrcID]:%d", (int)m_lppTex[iSrcID] );
		//
		return ERR_TEXTURE_VOID;
	}

	//中心点默认全为0，0，0
	D3DXVECTOR3 vCenter( 0.0f, 0.0f, 0.0f );

	//图象在世界中的位置
	D3DXVECTOR3 vPosition( x, y, z );

	//渲染
    if ( FAILED( hres = m_lpSpr->Draw( m_lppTex[iSrcID],
                          lpsrc_rect,
                          &vCenter,
                          &vPosition,
                          color ) ) )
	{
		//Write Error Report
		sprintf( g_strError_Report_Buffer, "Draw2D_Alpha() m_lpSpr->Draw() hres:%d", hres );
		//
		return ERR_DRAW_ALPHA;
	}

	return RIGHT_DRAW_ALPHA;
}

GraphicsError CDX9Graphics::Draw2D_Base(int iDescID, int iSrcID, int x, int y, float z, LPRECT lpSrcRect)
{
	HRESULT hres = 0;

	if ( NULL == m_lpSpr )
	{
		//Write Error Report
		sprintf( g_strError_Report_Buffer, "Draw2D_Base() m_lpSpr:%d", (int)m_lpSpr );
		//
		return ERR_SPRITE_VOID;
	}

	if ( iSrcID < 0 || iSrcID >= m_lppTex.size() )
	{
		//Write Error Report
		sprintf( g_strError_Report_Buffer, "Draw2D_Base() iSrcID < 0 || iSrcID >= m_lppTex.size() iSrcID:%d, m_lppTex.size():%d", iSrcID, m_lppTex.size() );
		//
		return ERR_NUMBER_OVER;
	}

	if ( NULL == m_lppTex[iSrcID] )
	{
		//Write Error Report
		sprintf( g_strError_Report_Buffer, "Draw2D_Base() m_lppTex[iSrcID]:%d", (int)m_lppTex[iSrcID] );
		//
		return ERR_TEXTURE_VOID;
	}

	//中心点默认全为0，0，0
	D3DXVECTOR3 vCenter( 0.0f, 0.0f, 0.0f );

	//图象在世界中的位置
	D3DXVECTOR3 vPosition( x, y, z );

	//渲染
    if ( FAILED( hres = m_lpSpr->Draw( m_lppTex[iSrcID],
                          lpSrcRect,
                          &vCenter,
                          &vPosition,
                          D3DCOLOR_COLORVALUE(1.0f,1.0f,1.0f,1.0f) ) ) )
	{
		//Write Error Report
		sprintf( g_strError_Report_Buffer, "Draw2D_Base() m_lpSpr->Draw() HRESULT:%d", hres );
		//
		return ERR_DRAW_BASE;
	}

	return RIGHT_DRAW_BASE;
}

GraphicsError CDX9Graphics::BeginSprite()
{
	HRESULT hres = 0;

	if ( m_lpSpr )
	{
		if ( FAILED( hres = m_lpSpr->Begin ( D3DXSPRITE_ALPHABLEND ) ) )
		{
			//Write Error Report
			sprintf( g_strError_Report_Buffer, "m_lpSpr->Begin() m_lpSpr:%d, HRESULT:%d", (int)m_lpSpr, hres );
			//
			return ERR_BEGIN_SPRITE;
		}
		else
			return RIGHT_BEGIN_SPRITE;
	}

	//Write Error Report
	sprintf( g_strError_Report_Buffer, "m_lpSpr->Begin() m_lpSpr:%d", (int)m_lpSpr );
	//
	return ERR_SPRITE_VOID;
}

GraphicsError CDX9Graphics::EndSprite()
{
	HRESULT hres = 0;

	if ( m_lpSpr )
	{
		if ( FAILED( hres = m_lpSpr->End() ) )
		{
			//Write Error Report
			sprintf( g_strError_Report_Buffer, "m_lpSpr->End() m_lpSpr:%d, HRESULT:%d", (int)m_lpSpr, hres );
			//
			return ERR_END_SPRITE;
		}
		else
			return RIGHT_END_SPRITE;
	}

	//Write Error Report
	sprintf( g_strError_Report_Buffer, "m_lpSpr->End() m_lpSpr:%d", (int)m_lpSpr );
	//
	return ERR_SPRITE_VOID;
}

GraphicsError CDX9Graphics::PrintText(int iID, int x, int y, char *text, DWORD color, int iwidth, int isize_x, int isize_y )
{
	HRESULT hres = 0;

	if ( iID < 0 || iID >= m_lppFont.size() )
	{
		//Write Error Report
		sprintf( g_strError_Report_Buffer, "iID < 0 || iID >= m_lppFont.size() iID:%d", iID );
		//
		return ERR_NUMBER_OVER;
	}

	if ( NULL == m_lppFont[iID] )
	{
		//Write Error Report
		sprintf( g_strError_Report_Buffer, "m_lppFont[iID]  iID:%d ", iID );
		//
		return ERR_FONT_VOID;
	}

	RECT rect;
	rect.left = x;
	rect.right = x + isize_x * iwidth;
	rect.top = y;
	rect.bottom = y + isize_y;

	char *Tmp = new char[MAX_PATH];

	if ( !Tmp )
	{
		//Write Error Report
		sprintf( g_strError_Report_Buffer, "char *Tmp = new char[MAX_PATH] Tmp: %s", Tmp );
		//
		return ERR_MEM_NEW;
	}

	int curlength = 0;

	int length = strlen(text) + 1;


	for ( int i = 0; i <= length / iwidth; i++ )
	{
		memset( Tmp, 0, MAX_PATH );
		//获取一行文本
		for ( int j = 0; j < (( i == length / iwidth ) ? length % iwidth : iwidth ); j++ )
		{
/*			HDC hdc = GetDC( m_hWnd );

			SIZE oldsize;
			SIZE cursize;

			//获取原长
			GetTextExtentPoint32( hdc, Tmp, strlen(Tmp), &oldsize );
			//获取下个字符长
			GetTextExtentPoint32( hdc, text, 1, &cursize );

			if ( *text < 0 )
			{
				if ( strlen(Tmp) )
				{
					if ( cursize.cx * 2 + oldsize.cx > iwidth )
						break;
				}
			}
			else
			{
				if ( strlen(Tmp) )
				{
					if ( cursize.cx + oldsize.cx > iwidth )
						break;
				}
			}
*/
			Tmp[j] = *text;
			if ( *text < 0 )
			{
				++text;
				++j;
				Tmp[j] = *text;	
				++curlength;
			}
			text++;
			++curlength;

			//字符写完
			if ( curlength >= length )
				break;
		}

		//显示文本
		if ( FAILED( hres = m_lppFont[iID]->DrawText( NULL, Tmp, strlen(Tmp), &rect, DT_LEFT, color ) ) )
		{
			delete [] Tmp;
			Tmp = NULL;

			//Write Error Report
			sprintf( g_strError_Report_Buffer, "PrintText() m_lpDev:%d, HRESULT:%d", (int)m_lpDev, hres );
			//
			return ERR_DRAW_TEXT;
		}

		rect.top		+= isize_y;
		rect.bottom		+= isize_y;
	}

	delete []Tmp;
	Tmp = NULL;

	return RIGHT_DRAW_TEXT;
}

GraphicsError CDX9Graphics::LoadPicFromFileInMemory(int iID, LPCVOID pSrcData, UINT SrcDataSize)
{
	HRESULT hres = 0;

	if ( iID < 0 || iID >= m_lppTex.size() )
	{
		//Write Error Report
		sprintf( g_strError_Report_Buffer, "iID < 0 || iID >= m_lppTex.size() iID:%d", iID );
		//
		return ERR_NUMBER_OVER;
	}

	if ( NULL == pSrcData || SrcDataSize <= 0 )
	{
		//Write Error Report
		sprintf( g_strError_Report_Buffer, "LoadPicFromFileInMemory's Memory is NULL" );
		//
		return ERR_MEMORY_NULL;
	}

	if ( NULL == m_lppTex[iID] )
	{
		//Write Error Report
		sprintf( g_strError_Report_Buffer, "LoadPicFromFileInMemory m_lppTex[iID]:%d", (int)m_lppTex[iID] );
		//
		return ERR_TEXTURE_VOID;
	}

	if ( FAILED( hres = D3DXCreateTextureFromFileInMemory( 
			m_lpDev, pSrcData, SrcDataSize, &m_lppTex[iID] ) ) )
	{
		m_lppTex[iID] = NULL;

		//Write Error Report
		string errreport;

		switch ( hres )
		{
		case D3DERR_INVALIDCALL:
			errreport = "参数错误 错误内型:D3DERR_INVALIDCALL";
			break;
		case D3DERR_NOTAVAILABLE:
			errreport = "设备不支持";
			break;
		case D3DERR_OUTOFVIDEOMEMORY:
			errreport = "显存不足";
			break;
		case D3DXERR_INVALIDDATA:
			errreport = "参数错误 错误内型:D3DXERR_INVALIDDATA";
			break;
		case E_OUTOFMEMORY:
			errreport = "内存不足";
			break;
		default:
			errreport = "其他错误结果";
			break;
		}
		sprintf( g_strError_Report_Buffer, "D3DXCreateTextureFromFileInMemory() hres:%s, file id:%d", errreport.c_str(), iID );
		//
		return ERR_LOAD_FROM_MEM;
	}

	return RIGHT_LOAD_FROM_MEM;
		
}

// release surface(texture) 
GraphicsError CDX9Graphics::ReleasePicSurface( int iID )
{
	if ( iID < 0 || iID >= m_lppTex.size() )
	{
		//Write Error Report
		sprintf( g_strError_Report_Buffer, "iID < 0 || iID >= m_lppTex.size() iID:%d", iID );
		//
		return ERR_NUMBER_OVER;
	}

	SAFE_RELEASE( m_lppTex[iID] );

	return RIGHT_RELEASE_SURFACE;
}

// only save the backbuffer
GraphicsError CDX9Graphics::SaveSurfaceToFile( char* filename, const int SaveType, LPRECT lpSrcRect )
{
	HRESULT hres = NULL;

	if ( NULL == filename )
	{
		//Write Error Report
		sprintf( g_strError_Report_Buffer, "SaveSurfaceToFile's filename is NULL" );
		//
		return ERR_MEMORY_NULL;
	}

	LPDIRECT3DSURFACE9 lpSurface = NULL;

	if ( FAILED( hres = m_lpDev->CreateOffscreenPlainSurface( 1024, 768, D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT, &lpSurface, NULL ) ) )
	{
		//Write Error Report
		sprintf( g_strError_Report_Buffer, "SaveSurfaceToFile: CreateOffscreenPlainSurface():%d", (int)hres );
		//
		return ERR_CREATE_OFF_SURFACE;
	}

	if ( FAILED( hres = m_lpDev->GetBackBuffer( 0, 0, D3DBACKBUFFER_TYPE_MONO, &lpSurface ) ) )
	{
		//release surface
		SAFE_RELEASE( lpSurface );

		//Write Error Report
		sprintf( g_strError_Report_Buffer, "SaveSurfaceToFile: GetbackBuffer():%d", (int)hres );
		//
		return ERR_GET_BACK_BUFFER;
	}

	D3DXIMAGE_FILEFORMAT fileformat = D3DXIFF_JPG;

	switch( SaveType )
	{
	case SAVE_TYPE_JPG:
		fileformat = D3DXIFF_JPG;
		break;
	case SAVE_TYPE_PNG:
		fileformat = D3DXIFF_PNG;
		break;
	case SAVE_TYPE_BMP:
		fileformat = D3DXIFF_BMP;
		break;
	default:
		fileformat = D3DXIFF_JPG;
		break;
	}

	if ( FAILED( hres = D3DXSaveSurfaceToFile( filename, fileformat, lpSurface, NULL, NULL ) ) )
	{
		//release surface
		SAFE_RELEASE( lpSurface );

		//Write Error Report
		sprintf( g_strError_Report_Buffer, "SaveSurfaceToFile: D3DXSaveSurfaceToFile():%d", (int)hres );
		//
		return ERR_SAVE_SURFACE;
	}

	SAFE_RELEASE( lpSurface );

	return RIGHT_SAVE_SURFACE;
}

// lock surface
GraphicsError CDX9Graphics::LockSurface( const int iID, LPRECT lprect, BYTE* &pByte, int &pitch )
{
	HRESULT hres = NULL;

	if ( iID < 0 || iID >= m_lppTex.size() )
	{
		//Write Error Report
		sprintf( g_strError_Report_Buffer, "iID < 0 || iID >= m_lppTex.size() iID:%d", iID );
		//
		return ERR_NUMBER_OVER;
	}

	D3DLOCKED_RECT lockrect;
	if ( FAILED( hres = m_lppTex[iID]->LockRect( 0, &lockrect, lprect, 0 ) ) )
	{
		//Write Error Report
		sprintf( g_strError_Report_Buffer, "LockRect failed iID:%d", iID );
		//
		return ERR_LOCK_SURFACE;
	}

	pByte = (BYTE*)lockrect.pBits;
	pitch = lockrect.Pitch;

	return RIGHT_LOCK_SURFACE;
}

// unlock surface
GraphicsError CDX9Graphics::UnlockSurface( const int iID )
{
	if ( iID < 0 || iID >= m_lppTex.size() )
	{
		//Write Error Report
		sprintf( g_strError_Report_Buffer, "iID < 0 || iID >= m_lppTex.size() iID:%d", iID );
		//
		return ERR_NUMBER_OVER;
	}

	m_lppTex[iID]->UnlockRect(0);

	return RIGHT_UNLOCK_SURFACE;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//From here lys added

/////////////////////////////////////////////////////////////////////////////////////////
//General
void CDX9Graphics::InitMatrix()
{
	D3DXMATRIX view_matrix;
	D3DXMATRIX projection_matrix;
	D3DXVECTOR3 eye_vector;
	D3DXVECTOR3 lookat_vector;
	D3DXVECTOR3 up_vector;

	//Here we build our View Matrix, think of it as our camera.

	//First we specify that our viewpoint is 8 units back on the Z-axis
	eye_vector=D3DXVECTOR3( 0.0f, 0.0f,8.0f );

	//We are looking towards the origin
	lookat_vector=D3DXVECTOR3( 0.0f, 0.0f, 0.0f );

	//The "up" direction is the positive direction on the y-axis
	up_vector=D3DXVECTOR3(0.0f,1.0f,0.0f);

	D3DXMatrixLookAtLH(&view_matrix,&eye_vector,
									&lookat_vector,
									&up_vector);

	//Since our 'camera' will never move, we can set this once at the
	//beginning and never worry about it again
	m_lpDev->SetTransform(D3DTS_VIEW,&view_matrix);


	D3DXMatrixPerspectiveFovLH(&projection_matrix, //Result Matrix
								D3DX_PI/4,//Field of View, in radians.(PI/4) is typical (90 degrees)
								( 640 / 480.0f ),     //Aspect ratio
								1.0f,     //Near view plane
								100.0f ); // Far view plane

	//Our Projection matrix won't change either, so we set it now and never touch
	//it again.
	m_lpDev->SetTransform( D3DTS_PROJECTION, &projection_matrix );

}

/////////////////////////////////////////////////////////////////////////////////////////
//primitive rendering 
//main function of 2D geometric shape render
GraphicsError CDX9Graphics::Draw2DShape( ShapeType theType, void* pVertexBuffer, int iPrimitiveNumber)
{
	switch (theType)
	{
	case ShapePoint:
		return DrawPoint2D( (IDirect3DVertexBuffer9*)pVertexBuffer, iPrimitiveNumber );
	case ShapeLine:
		return DrawLine2D( (IDirect3DVertexBuffer9*)pVertexBuffer, iPrimitiveNumber );
	case ShapeTriangleStrip:
		return DrawTrianglestrip2D( (IDirect3DVertexBuffer9*)pVertexBuffer, iPrimitiveNumber );

	default:
		return ERR_D3D_SHAPE;
	}
}

//main function of 3D geometric shape render
GraphicsError CDX9Graphics::Draw3DShape( ShapeType theType, void* pVertexBuffer, int iPrimitiveNumber, float* fRotate )
{
	//init world mitrix
	D3DXMATRIX matWorld;
	D3DXMATRIX trans_matrix;
	//init vars of rotating
	D3DXMATRIX rot_x_matrix;   
	D3DXMATRIX rot_z_matrix;   
	D3DXMATRIX rot_y_matrix;   
	D3DXMATRIX rot_matrix;     
	float rot_x=fRotate[0];    
	float rot_y=fRotate[1];    
	float rot_z=fRotate[2];    

	//set rotating matrix
	D3DXMatrixRotationY(&rot_y_matrix,rot_y);
	D3DXMatrixRotationX(&rot_x_matrix,rot_x);
	D3DXMatrixRotationZ(&rot_z_matrix,rot_z);

	//Combine the 2 matrices to get our final Rotation Matrix
	/////////////////////////////////
	/*here needs further alteration*/
	/////////////////////////////////
	D3DXMatrixMultiply(&rot_matrix,&rot_x_matrix,&rot_y_matrix);

	//Translate out cube in/out of the screen
	D3DXMatrixTranslation(&trans_matrix,0.0f,0.0f,8.0f);

	//Build our final World Matrix
//	D3DXMatrixMultiply(&matWorld,&rot_matrix,&trans_matrix);

	//Set our World Matrix
	m_lpDev->SetTransform(D3DTS_WORLD,&rot_matrix );

	switch (theType)
	{
	case ShapeLine:
		return DrawLine3D( (IDirect3DVertexBuffer9*)pVertexBuffer, iPrimitiveNumber );
	case ShapeTriangleStrip:
		return DrawTrianglestrip3D( (IDirect3DVertexBuffer9*)pVertexBuffer, iPrimitiveNumber );
	default:
		return ERR_D3D_SHAPE;
	}
}

//creater vertex buffer 
GraphicsError CDX9Graphics::CreateVertexBuffer( void** ppBuffer, int iBufferSize, bool b2DBuffer)
{
	HRESULT hr;


	if( b2DBuffer )
	{
		//this creates the xyzrhw format vertex
		hr=m_lpDev->CreateVertexBuffer( iBufferSize*sizeof(CustomVertex2D ), //Size of memory to be allocated
																//Number of vertices * size of a vertex
											D3DUSAGE_WRITEONLY,  //We never need to read from it so
																//we specify write only, it's faster
											D3D9_CUSTOMVERTEX2D,  //Our custom vertex specifier (coordinates & a colour)
											D3DPOOL_MANAGED,     //Tell DirectX to manage the memory of this resource
											(IDirect3DVertexBuffer9**)ppBuffer,
											NULL);              
	}
	else
	{
		//this creates the zyx format vertex
		hr=m_lpDev->CreateVertexBuffer( iBufferSize*sizeof(CustomVertex3D ), //Size of memory to be allocated
																//Number of vertices * size of a vertex
											D3DUSAGE_WRITEONLY,  //We never need to read from it so
																//we specify write only, it's faster
											D3D9_CUSTOMVERTEX3D,  //Our custom vertex specifier (coordinates & a colour)
											D3DPOOL_MANAGED,     //Tell DirectX to manage the memory of this resource
											(IDirect3DVertexBuffer9**)ppBuffer,
											NULL);              
	}


	if(FAILED(hr)){
		//Write Error Report
		sprintf( g_strError_Report_Buffer, "Create vertex buffer error." );
		//
		return ERR_CREATE_BUFFER;
	}
	else
		return RIGHT_CREATE_BUFFER;
}

//modify vertex buffer
GraphicsError CDX9Graphics::UpdateVertexBuffer( void* pVertex, void* pBuffer, size_t Size )
{
	//safty check
	if( NULL ==  pBuffer || NULL == pVertex)
		return ERR_LOCK_BUFFER;


	HRESULT hr;
	IDirect3DVertexBuffer9* pVB = (IDirect3DVertexBuffer9*)pBuffer;
	void *vb_vertices = NULL;

	hr=pVB->Lock(0, //Offset, we want to start at the beginning
					0, //SizeToLock, 0 means lock the whole thing
					&vb_vertices, //If successful, this will point to the data in the VB
					0);  //Flags, nothing special
	if(FAILED(hr)){
		//Write Error Report
		sprintf( g_strError_Report_Buffer, "Create vertex buffer error." );
		//
		return ERR_LOCK_BUFFER;
	}

	memcpy(vb_vertices, pVertex, Size );

	//Unlock so Direct3D knows we're done and can do any behind-the-scenes magic required
	pVB->Unlock();


	return RIGHT_LOCK_BUFFER;
}

//release the vertex buffer
void CDX9Graphics::ReleaseVertexBuffer( void* pBuffer )
{
	IDirect3DVertexBuffer9* pVertexBuffer = (IDirect3DVertexBuffer9*)pBuffer;
	SAFE_RELEASE( pVertexBuffer );
}



	
//Draw shape line 2D
GraphicsError CDX9Graphics::DrawLine2D( IDirect3DVertexBuffer9* pVertexBuffer, int iPrimitiveNumber )
{
	m_lpDev->SetFVF( D3D9_CUSTOMVERTEX2D );

	m_lpDev->SetStreamSource(0,pVertexBuffer,0,sizeof(CustomVertex2D));

	m_lpDev->DrawPrimitive(D3DPT_LINELIST,0,iPrimitiveNumber);

	return RIGHT_D3D_SHAPE;
}
//Draw shape line 3D
GraphicsError CDX9Graphics::DrawLine3D( IDirect3DVertexBuffer9* pVertexBuffer, int iPrimitiveNumber )
{
	m_lpDev->SetFVF( D3D9_CUSTOMVERTEX3D );

	m_lpDev->SetStreamSource(0,pVertexBuffer,0,sizeof(CustomVertex3D));

	m_lpDev->DrawPrimitive(D3DPT_LINELIST,0,iPrimitiveNumber);

	return RIGHT_D3D_SHAPE;
}

//Draw shape point 2D
GraphicsError CDX9Graphics::DrawPoint2D( IDirect3DVertexBuffer9* pVertexBuffer, int iPrimitiveNumber )
{
	m_lpDev->SetFVF( D3D9_CUSTOMVERTEX2D );

	m_lpDev->SetStreamSource(0,pVertexBuffer,0,sizeof(CustomVertex2D));

	m_lpDev->DrawPrimitive(D3DPT_POINTLIST,0,iPrimitiveNumber);

	return RIGHT_D3D_SHAPE;
}
//Draw shape point 3D
GraphicsError CDX9Graphics::DrawPoint3D( IDirect3DVertexBuffer9* pVertexBuffer, int iPrimitiveNumber )
{
	m_lpDev->SetFVF( D3D9_CUSTOMVERTEX3D );

	m_lpDev->SetStreamSource(0,pVertexBuffer,0,sizeof(CustomVertex3D));

	m_lpDev->DrawPrimitive(D3DPT_POINTLIST,0,iPrimitiveNumber);

	return RIGHT_D3D_SHAPE;
}

//Draw shape triangle strip 2D
GraphicsError CDX9Graphics::DrawTrianglestrip2D( IDirect3DVertexBuffer9* pVertexBuffer, int iPrimitiveNumber )
{
	m_lpDev->SetFVF( D3D9_CUSTOMVERTEX2D );

	m_lpDev->SetStreamSource(0,pVertexBuffer,0,sizeof(CustomVertex2D));

	m_lpDev->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,iPrimitiveNumber);

	return RIGHT_D3D_SHAPE;
}
//Draw shape triangle strip 3D
GraphicsError CDX9Graphics::DrawTrianglestrip3D( IDirect3DVertexBuffer9* pVertexBuffer, int iPrimitiveNumber )
{
	m_lpDev->SetFVF( D3D9_CUSTOMVERTEX3D );

	m_lpDev->SetStreamSource(0,pVertexBuffer,0,sizeof(CustomVertex3D));

	m_lpDev->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,iPrimitiveNumber);

	return RIGHT_D3D_SHAPE;
}

//lys added end
/////////////////////////////////////////////////////////////////////////////////////////////////
