#include "camera.h"
#include "stdafx.h"

Camera::Camera(void)
{
	m_fCameraDistance = 1.0;
	m_fZoomStep		  = 0.02;
	m_pGraphics = NULL;
}

Camera::~Camera(void)
{
}


////////////////////////////////////////////////////////////////////////////////
//control funs
void Camera::SetDefaultPosition()
{
	float fEyePos[3]  = {0.0, 3.0, -5.5};
	float fLookPos[3] = {0.0, 0.0, 0.0};
	float fUpDrct[3]  = {0.0, 1.0, 0.0};

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
	float fZoomingUnit = 0.0;

	for( int i = 0; i < 3; ++i )
	{
		//Get zooming unit
		fZoomingUnit = m_pfEyePos[i] / m_fCameraDistance;

		//Update New camera distance
		m_fCameraDistance -= m_fZoomStep;

		//Update camera position
		m_pfEyePos[i] = fZoomingUnit * m_fCameraDistance;
	}

	UpdateCamera();
}

void Camera::ZoomOut()
{
	float fZoomingUnit = 0.0;

	for( int i = 0; i < 3; ++i )
	{
		//Get zooming unit
		fZoomingUnit = m_pfEyePos[i] / m_fCameraDistance;

		//Update New camera distance
		m_fCameraDistance += m_fZoomStep;

		//Update camera position
		m_pfEyePos[i] = fZoomingUnit * m_fCameraDistance;
	}

	UpdateCamera();
}



