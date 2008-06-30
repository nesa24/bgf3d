#pragma once

#include "Canvas.h"

class Camera
{
public:
	Camera(void);
	~Camera(void);

	//Control funs
public:
	void SetDefaultPosition();
	void UpdateCamera();
	bool InitCamera( CGameGraphics* pGraphics );

	void ZoomIn();
	void ZoomOut();
	
private:
	float m_pfEyePos[3];
	float m_pfLookPos[3];
	float m_pfUpDrct[3];

	//distance from camera to original point, 1.0 as default distance
	float m_fCameraDistance;
	//Scale of each zooming
	float m_fZoomStep;

	CGameGraphics* m_pGraphics;
};
