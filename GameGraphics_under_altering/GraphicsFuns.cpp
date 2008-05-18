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

	//��ȡ��ǰʱ��
	GetLocalTime( &curtime );

	sprintf( strreport, "Error Report Time: %d:%d:%d", curtime.wHour, curtime.wMinute, curtime.wSecond );

	fout << strreport << endl;

	//д����󱨸��ĵ�
	switch ( error )
	{
		case ERR_CREATE_3D:			//����3Dʧ��
			{
				fout << "��������:����3D����ʧ��" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_CREATE_MODE:		//����ģʽʧ��
			{
				fout << "��������:����ģʽʧ��" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_CREATE_DEVICE:		//����ʧ��
			{
				fout << "��������:�����豸ʧ��" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_VIRTUAL:			//�麯������
			{
				fout << "��������:���û����麯��" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_BEGIN_RENDER:		//��ʼ��Ⱦʧ��
			{
				fout << "��������:BeginRender()ʧ��" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_END_RENDER:		//������Ⱦʧ��
			{
				fout << "��������:EndRender()ʧ��" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_DEVICE_VOID:		//�豸ʧЧ
			{
				fout << "��������:�豸��δ�������Ѿ��ͷ�" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_SPRITE_VOID:		//�������Ϊ��
			{
				fout << "��������:������δ�������Ѿ��ͷ�" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_TEXTURE_VOID:		//��ԴΪ��
			{
				fout << "��������:ͼ����Դ��δ�������Ѿ��ͷ�" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_FONT_VOID:			//����Ϊ��
			{
				fout << "��������:������Դ��δ�������Ѿ��ͷ�" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_FILL_SURFACE:		//ҳ����ɫʧ��
			{
				fout << "��������:ҳ�������ɫʧ��" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_SETUP_MATRICES:	//�����ӽ�ʧ��
			{
				fout << "��������:�ӽ��趨ʧ��" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_PRESENT:			//��תҳ��ʧ��
			{
				fout << "��������:��ҳʧ��" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_SET_LIGHTING:		//���ù���ʧ��
			{
				fout << "��������:���õƹ�ʧ��" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_SET_CULL:			//���������λ��Ʒ���ʧ��
			{
				fout << "��������:������Ⱦ������˳��ʧ��" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_SET_ZBUFFER:		//����Z-BUFFERʧ��
			{
				fout << "��������:����Z-BUFFERʧ��" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_CREATE_FONT:		//��������ʧ��
			{
				fout << "��������:��������ʧ��" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_CREATE_SURFACE:	//����ҳ��ʧ��
			{
				fout << "��������:����ҳ��ʧ��" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_CREATE_SPRITE:		//��������ʧ��
			{
				fout << "��������:��������ʧ��" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_LOAD_PIC:			//����ͼ����Դʧ��
			{
				fout << "��������:����ͼ����Դʧ��" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_BEGIN_SPRITE:		//��ʼ��Ⱦ����ʧ��
			{
				fout << "��������:BeginSprite()ʧ��" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_END_SPRITE:		//������Ⱦ����ʧ��
			{
				fout << "��������:EndSprite()ʧ��" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_SET_WORLD_POS:		//������������ʧ��
			{
				fout << "��������:������������ʧ��" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_DRAW_ADVANCE:		//���ƺ�������ʧ��
			{
				fout << "��������:Draw_Advance()ʧ��" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_DRAW_ALPHA:		//���ƺ�������ʧ��
			{
				fout << "��������:Draw_Alpha()ʧ��" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_DRAW_BASE:			//���ƺ�������ʧ��
			{
				fout << "��������:Draw_Base()ʧ��" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_NUMBER_OVER:		//�������
			{
				fout << "��������:��ֵ���" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_MEM_NEW:			//������Դʧ��
			{
				fout << "��������:��̬�����ڴ�ʧ��" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_DRAW_TEXT:			//��������ʧ��
			{
				fout << "��������:��������ʧ��" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_MEMORY_NULL:		//ָ���ڴ�Ϊ��
			{
				fout << "��������:ָ���ڴ�Ϊ��" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_LOAD_FROM_MEM:		//���ڴ������Դʧ��
			{
				fout << "��������:���ڴ������Դʧ��" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_CREATE_OFF_SURFACE:	//������̬����ҳ��ʧ��
			{
				fout << "��������:������̬����ҳ��ʧ��" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_GET_BACK_BUFFER:	//��ȡ��̨ҳ��ʧ��
			{
				fout << "��������:��ȡ��̨ҳ��ʧ��" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_SAVE_SURFACE:		//����ҳ��ʧ��
			{
				fout << "��������:����ҳ��ʧ��" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		case ERR_LOCK_SURFACE:		//��ҳ��ʧ��
			{
				fout << "��������:��ҳ��ʧ��" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
		default:					//����
			{
				fout << "δ֪����" << endl;
				fout << g_strError_Report_Buffer << endl;
			}
			break;
	}
	return true;
}