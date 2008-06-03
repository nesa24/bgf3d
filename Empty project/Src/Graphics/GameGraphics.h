
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
	//�ͷ�Ŀ��ҳ����Դ
	//����:ҳ���ID
	//���ͷ���Դռ�õ��ڴ�
	virtual GraphicsError ReleaseSurface( int iID );
	//��������
	//����:����ID,����x,y,����ָ��,��ɫ,���г���(����),�ַ����(����),�ַ��о�(����)
	virtual GraphicsError PrintText(int iID, int x, int y, char *text, DWORD color, int iwidth = 60, int isize_x = 12, int isize_y = 20);
	//�رվ���
	//�ʹ򿪾������Ӧ,��ʹ�þ���֮��������
	virtual GraphicsError EndSprite();
	//�򿪾���
	//�͹رվ������Ӧ,��ʹ�þ���֮ǰ�������
	virtual GraphicsError BeginSprite();
	//����ͼ��
	//����:Ŀ��ҳ��ID,Դҳ��ID,����x,y,ҳ�����ڲ���,Դҳ�����
	//û�б���,��ɫ,��״����ĸ��Ӳ���
	virtual GraphicsError Draw2D_Base(int iDescID, int iSrcID, int x, int y, float z = 1.0f, LPRECT lpSrcRect = NULL );
	//����ͼ��
	//����:Ŀ��ҳ��ID,Դҳ��ID,����x,y,ҳ�����ڲ���,Ŀ��ҳ�����,Դҳ�����,��ɫֵ,͸����ֵ(Ŀǰû����)͸��ֵ������ǰ�����ɫֵ��
	//û�б���,��״����ĸ��Ӳ���,����˶���ɫ�Ĳ����ӿ�,��ִ���ٶȺ�ǰһ����һ����
	virtual GraphicsError Draw2D_Alpha(int iDescID, int iSrcID, int x, int y, float z = 1.0f, LPRECT lpdesc_rect = NULL, LPRECT lpsrc_rect = NULL, DWORD color = 0xffffffff, int alpha = 0);
	//����ͼ��
	//����:Ŀ��ҳ��ID,Դҳ��ID,����x,y,ҳ�����ڲ���,Ŀ��ҳ�����,Դҳ�����,��ɫֵ,͸����ֵ(Ŀǰû����)͸��ֵ������ǰ�����ɫֵ��,
	//��ת�Ƕ�,X�����ű���,Y�����ű���
	//��������2Dͼ��Ĳ���,�����˶���ת,���ŵĲ���,����Ϊ���������������޸�,�����ڰ����˶��Եľ������
	//�ٶ���Ӱ��,����ǰ��ĺ�����
	virtual GraphicsError Draw2D_Advance(int iDescID, int iSrcID, int x, int y, float z = 1.0f, LPRECT lpdesc_rect = NULL, LPRECT lpsrc_rect = NULL, DWORD color = 0xffffffff, int alpha = 0, int angle = 0, float size_x = 1.0f, float size_y = 1.0f);
	//������ԴͼƬ
	//����:ҳ��ID,��Դ�ļ���
	//��ԴͼƬ�ߴ��������2,4,8,16,32,64,128,256,512,1024,��ò�Ҫ����1024,��Ϊͼ����Դ̫��,������Ӱ��ͼ�����Ч��
	//�������������,Ӳ�����Զ����ŵ��涨�ߴ�
	virtual GraphicsError LoadPic( int iID, char* filename );
	//����ҳ��
	//����:ҳ��ĳߴ��,��
	//���ڲ���û��ʵ������,ҳ��̶�������ԴͼƬ�ĳߴ�
	virtual GraphicsError CreateSurface( int width, int height );
	//��������
	//����:��������,��������(����:"����"),�Ƿ����,�Ƿ�б��
	virtual GraphicsError DXCreateFont( int iSize, char *strType, BOOL bBold = FALSE, BOOL bSharp = FALSE );
	//��ʼ��������Ⱦ���Ե�
	virtual GraphicsError InitGeometry();
	//��Ⱦ����,ÿ��Ҫ���ô˺����������������Ⱦ
	virtual GraphicsError Render();
	//���ҳ��
	//����:ҳ��ID,��ɫ
	virtual GraphicsError FillSurface( int iID, DWORD color );
	//���ҳ��ָ������
	//����:ҳ��ID,��ɫ,����
	virtual GraphicsError FillSurfaceRect( int iID, DWORD color, LPRECT lpR = NULL );
	//�ر���Ⱦ����
	//�Ϳ�ʼ��Ⱦ�������Ӧ,����ɶԳ���
	virtual GraphicsError EndRender();
	//��ʼ��Ⱦ����
	//�͹ر���Ⱦ�������Ӧ,����ɶԳ���
	virtual GraphicsError BeginRender();
	//�ͷ�������Դ
	virtual GraphicsError ShutGraphics();
	//�����ӽǺ���������
	virtual GraphicsError SetupMatrices();
	//��ʼ���豸
	//����:���ھ��,�Ƿ�ȫ��,ȫ��ʱ�ĳߴ�
	virtual GraphicsError InitGraphics( HWND hwnd, BOOL bWindow = TRUE, int width = 800, int height = 600 );
	//����ҳ����Դ���ڴ�������
	//����:ҳ��ID,ҳ����Դָ��,��Դ����
	virtual GraphicsError LoadPicFromFileInMemory(int iID, LPCVOID pSrcData, UINT SrcDataSize);
	//�ͷ�Ŀ��ҳ����Դ
	//����:ҳ���ID
	//���ͷ���Դռ�õ��ڴ�
	virtual GraphicsError ReleasePicSurface( int iID );
	//��¼��ǰ��ʾҳ�浽�ļ���
	//����:��¼�ļ���,�ļ�����,����ҳ��ķ�Χ
	virtual GraphicsError SaveSurfaceToFile( char* filename, const int SaveType = SAVE_TYPE_JPG, LPRECT lpSrcRect = NULL );
	//��סҳ��
	//����:Ŀ��ID,��Χ(NULLΪȫ��),������ָ��,���ص��г���
	virtual GraphicsError LockSurface( const int iID, LPRECT lprect, BYTE* &pByte, int &pitch );
	//����ҳ��
	//����:Ŀ��ID
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


