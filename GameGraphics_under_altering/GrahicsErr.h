#ifndef GRAPHICSERR_H
#define GRAPHICSERR_H

enum GraphicsError
{
	ERR_CREATE_3D = 0,		//����3Dʧ��
	ERR_CREATE_MODE,		//����ģʽʧ��
	ERR_CREATE_DEVICE,		//����ʧ��
	ERR_VIRTUAL,			//�麯������
	ERR_BEGIN_RENDER,		//��ʼ��Ⱦʧ��
	ERR_END_RENDER,			//������Ⱦʧ��
	ERR_DEVICE_VOID,		//�豸ʧЧ
	ERR_SPRITE_VOID,		//�������Ϊ��
	ERR_TEXTURE_VOID,		//��ԴΪ��
	ERR_FONT_VOID,			//����Ϊ��
	ERR_FILL_SURFACE,		//ҳ����ɫʧ��
	ERR_SETUP_MATRICES,		//�����ӽ�ʧ��
	ERR_PRESENT,			//��תҳ��ʧ��
	ERR_SET_LIGHTING,		//���ù���ʧ��
	ERR_SET_CULL,			//���������λ��Ʒ���ʧ��
	ERR_SET_ZBUFFER,		//����Z-BUFFERʧ��
	ERR_CREATE_FONT,		//��������ʧ��
	ERR_CREATE_SURFACE,		//����ҳ��ʧ��
	ERR_CREATE_SPRITE,		//��������ʧ��
	ERR_LOAD_PIC,			//����ͼ����Դʧ��
	ERR_BEGIN_SPRITE,		//��ʼ��Ⱦ����ʧ��
	ERR_END_SPRITE,			//������Ⱦ����ʧ��
	ERR_SET_WORLD_POS,		//������������ʧ��
	ERR_DRAW_ADVANCE,		//���ƺ�������ʧ��
	ERR_DRAW_ALPHA,			//���ƺ�������ʧ��
	ERR_DRAW_BASE,			//���ƺ�������ʧ��
	ERR_NUMBER_OVER,		//�������
	ERR_MEM_NEW,			//������Դʧ��
	ERR_DRAW_TEXT,			//��������ʧ��
	ERR_MEMORY_NULL,		//ָ���ڴ�Ϊ��
	ERR_LOAD_FROM_MEM,		//���ڴ������Դʧ��
	ERR_CREATE_OFF_SURFACE,	//������̬����ҳ��ʧ��
	ERR_GET_BACK_BUFFER,	//��ȡ��̨ҳ��ʧ��
	ERR_SAVE_SURFACE,		//����ҳ��ʧ��
	ERR_LOCK_SURFACE,		//��ҳ��ʧ��

	RIGHT_CREATE,			//�����ɹ�
	RIGHT_RELEASE,			//�ͷ���Դ�ɹ�
	RIGHT_BEGIN_RENDER,		//��ʼ��Ⱦ�ɹ�
	RIGHT_END_RENDER,		//������Ⱦ�ɹ�
	RIGHT_FILL_SURFACE,		//ҳ����ɫ�ɹ�
	RIGHT_SETUP_MATRICES,	//�����ӽǳɹ�
	RIGHT_PRESENT,			//��תҳ��ɹ�
	RIGHT_SET_STATE,		//����״̬�ɹ�
	RIGHT_CREATE_FONT,		//��������ɹ�
	RIGHT_CREATE_SURFACE,	//����ҳ��ɹ�
	RIGHT_LOAD_PIC,			//����ͼ����Դ�ɹ�
	RIGHT_DRAW_ADVANCE,		//���Ƴɹ�
	RIGHT_DRAW_ALPHA,		//���Ƴɹ�
	RIGHT_DRAW_BASE,		//���Ƴɹ�
	RIGHT_BEGIN_SPRITE,		//��ʼ��Ⱦ����ɹ�
	RIGHT_END_SPRITE,		//������Ⱦ����ɹ�
	RIGHT_DRAW_TEXT,		//�������ֳɹ�
	RIGHT_LOAD_FROM_MEM,	//���ڴ������Դ�ɹ�
	RIGHT_RELEASE_SURFACE,	//�ͷ���Դ�ɹ�
	RIGHT_SAVE_SURFACE,		//����ҳ��ɹ�
	RIGHT_LOCK_SURFACE,		//��ҳ��ɹ�
	RIGHT_UNLOCK_SURFACE,	//����ҳ��ɹ�

	//ly's added flag
	ERR_D3D_SHAPE,			//D3D��ͼʧ��
	ERR_CREATE_BUFFER,		//��������bufferʧ��
	ERR_LOCK_BUFFER,		//��������bufferʧ��
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