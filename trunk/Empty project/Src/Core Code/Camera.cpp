#include "camera.h"
#include "stdafx.h"

//const values
const float fZoomInRestrict = 0.3f;
const float fDefaultCameraPos[3] = {0.0, 3.0, -5.5};

Camera::Camera(void)
{
	m_fCameraDistance = 1.0f;
	m_fZoomStep		  = 0.01f;
	m_pGraphics		  = NULL;
}

Camera::~Camera(void)
{
}


////////////////////////////////////////////////////////////////////////////////
//control funs
void Camera::SetDefaultPosition()
{
	//set defualt camera pos
	float fEyePos[3]  = {fDefaultCameraPos[AxisX], fDefaultCameraPos[AxisY], fDefaultCameraPos[AxisZ]};
	float fLookPos[3] = {0.0, 0.0, 0.0};
	float fUpDrct[3]  = {0.0, 1.0, 0.0};
	//set default distance proportion
	m_fCameraDistance = 1.0;

	memcpy( (void*)m_pfEyePos, (void*)fEyePos, sizeof(fEyePos) );
	memcpy( (void*)m_pfLookPos, (void*)fLookPos, sizeof(fEyePos) );
	memcpy( (void*)m_pfUpDrct, (void*)fUpDrct, sizeof(fEyePos) );

	UpdateCamera();
}

void Camera::UpdateCamera()
{
	if( NULL == m_pGraphics 
		|| NULL == m_pfEyePos  
		|| NULL == m_pfLookPos
		|| NULL == m_pfUpDrct  )
		return;

	m_pGraphics->SetCamera( m_pfEyePos, m_pfLookPos, m_pfUpDrct);
}

bool Camera::InitCamera( CGameGraphics* pGraphics )
{
	if( NULL == pGraphics )
		return false;

	m_pGraphics = pGraphics;
	return true;
}

void Camera::ZoomIn()
{
	//zooming restrict
	if( m_fCameraDistance < fZoomInRestrict )
		return;

	float fZoomingUnit[3];
	int i = 0;

	for( i = 0; i < 3; ++i )
		//Get zooming unit
		fZoomingUnit[i] = m_pfEyePos[i] / m_fCameraDistance;

	//Update New camera distance
	m_fCameraDistance -= m_fZoomStep;

	for( i = 0; i < 3; ++i )
		//Update camera position
		m_pfEyePos[i] = fZoomingUnit[i] * m_fCameraDistance;

	UpdateCamera();
}

void Camera::ZoomOut()
{
	float fZoomingUnit[3];
	int i = 0;

	for( i = 0; i < 3; ++i )
		//Get zooming unit
		fZoomingUnit[i] = m_pfEyePos[i] / m_fCameraDistance;

	//Update New camera distance
	m_fCameraDistance += m_fZoomStep;

	for( i = 0; i < 3; ++i )
		//Update camera position
		m_pfEyePos[i] = fZoomingUnit[i] * m_fCameraDistance;

	UpdateCamera();
}



