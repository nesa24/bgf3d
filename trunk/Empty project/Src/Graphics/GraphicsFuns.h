#ifndef GRAPHICSFUNS_H
#define GRAPHICSFUNS_H

#include "GameGraphics.h"
#include "GrahicsErr.h"

#define _DEBUG_GRAPHICS

//����ͼ�ο�����
//����:���ھ��,�Ƿ�ȫ��,ȫ���µĿ�,ȫ���µĸ�
//�ⲿֱ�ӵ��ô˺�����������,����ֱ�ӵ���CGameGraphics����ĳ�ʼ������
CGameGraphics GAMEGRAPHICS_API  *CreateGameGraphics( HWND hwnd, BOOL bWindow, int width, int height );

bool GAMEGRAPHICS_API ReportError( GraphicsError error );

#endif

