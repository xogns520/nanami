#include "StdAfx.h"
#include "cCamera.h"


cCamera::cCamera(void)
: m_vEye(0, 0, -5)
, m_vLookAt(0, 0, 0)
, m_vUp(0, 1, 0)
, m_isLButtonDown(false)
, m_fAngleX(0.0f)
, m_fAngleY(0.0f)
, m_fDistance(5.0f)
{
	m_ptPrevMouse.x = 0;
	m_ptPrevMouse.y = 0;
}


cCamera::~cCamera(void)
{
}

void cCamera::Setup()
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	D3DXMATRIXA16 matView, matProj;

	D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vLookAt, &m_vUp);

	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);

	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4.0f, rc.right / (float)rc.bottom, 1.0f, 1000.0f);

	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}

void cCamera::Update(D3DXVECTOR3* pTarget)
{
	m_vEye = D3DXVECTOR3(0, 0, -m_fDistance);
	m_vLookAt = D3DXVECTOR3(0, 0, 0);

	D3DXMATRIXA16 matRotX, matRotY;

	D3DXMatrixRotationX(&matRotX, m_fAngleX);
	D3DXMatrixRotationY(&matRotY, m_fAngleY);

	D3DXMATRIXA16 matRot = matRotX * matRotY;

	D3DXVec3TransformCoord(&m_vEye, &m_vEye, &matRot);

	if (pTarget)
	{
		m_vEye = m_vEye + *pTarget;
		m_vLookAt = m_vLookAt + *pTarget;
	}

	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vLookAt, &m_vUp);
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);
}

void cCamera::Update(float Angle, D3DXVECTOR3 * pTarget)
{
	m_vEye = D3DXVECTOR3(0, 2.5, -m_fDistance);
	//m_vEye = D3DXVECTOR3(0, 2.5, -4.5);
	m_vLookAt = D3DXVECTOR3(0, 0.7, 0);

	D3DXMATRIXA16 matRotX, matRotY;

	D3DXMatrixRotationX(&matRotX, m_fAngleX);
	//D3DXMatrixRotationY(&matRotY, m_fAngleY);		//마우스로 y조절
	D3DXMatrixRotationY(&matRotY, Angle);			//캐릭터로 y조절

	D3DXMATRIXA16 matRot = matRotX * matRotY;

	D3DXVec3TransformCoord(&m_vEye, &m_vEye, &matRot);

	if (pTarget)
	{
		m_vEye = m_vEye + *pTarget;
		m_vLookAt = m_vLookAt + *pTarget;
	}

	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vLookAt, &m_vUp);
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);
}

void cCamera::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_MOUSEWHEEL:
		m_fDistance -= GET_WHEEL_DELTA_WPARAM(wParam) / 100.f;
		break;
	case WM_LBUTTONDOWN:
		m_ptPrevMouse.x = LOWORD(lParam);
		m_ptPrevMouse.y = HIWORD(lParam);
		m_isLButtonDown = true;
		break;
	case WM_LBUTTONUP:
		m_isLButtonDown = false;
		break;
	case WM_MOUSEMOVE:
	{
						 if (m_isLButtonDown)
						 {
							 POINT ptCurrMouse;
							 ptCurrMouse.x = LOWORD(lParam);
							 ptCurrMouse.y = HIWORD(lParam);

							 int nDeltaX = ptCurrMouse.x - m_ptPrevMouse.x;
							 int nDeltaY = ptCurrMouse.y - m_ptPrevMouse.y;

							 m_fAngleX += nDeltaY / 100.f;

							 if (m_fAngleX <= -D3DX_PI / 2 + EPSILON)
								 m_fAngleX = -D3DX_PI / 2 + EPSILON;

							 if (m_fAngleX >= D3DX_PI / 2 - EPSILON)
								 m_fAngleX = D3DX_PI / 2 - EPSILON;

							 m_fAngleY += nDeltaX / 100.f;

							 m_ptPrevMouse = ptCurrMouse;
						 }
	}
		break;
	}
}

void cCamera::FrustumUpdate()
{
	float x = 1, y = 1, z = 1;

	m_arrBox[0] = D3DXVECTOR3(-x, y, 0);
	m_arrBox[1] = D3DXVECTOR3(x, y, 0);
	m_arrBox[2] = D3DXVECTOR3(-x, -y, 0);
	m_arrBox[3] = D3DXVECTOR3(x, -y, 0);
	m_arrBox[4] = D3DXVECTOR3(-x, y, z);
	m_arrBox[5] = D3DXVECTOR3(x, y, z);
	m_arrBox[6] = D3DXVECTOR3(-x, -y, z);
	m_arrBox[7] = D3DXVECTOR3(x, -y, z);

	D3DXMATRIX projMat, projInvMat, viewMat, viewInvMat;
	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &projMat);
	D3DXMatrixInverse(&projInvMat, 0, &projMat);
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &viewMat);
	D3DXMatrixInverse(&viewInvMat, 0, &viewMat);

	for (int i = 0; i < 8; i++)
	{
		D3DXVec3TransformCoord(&m_arrBox[i], &m_arrBox[i], &projInvMat);
		D3DXVec3TransformCoord(&m_arrBox[i], &m_arrBox[i], &viewInvMat);
	}

	D3DXPlaneFromPoints(&m_arrPlane[PFront], &m_arrBox[FLT], &m_arrBox[FRT], &m_arrBox[FLB]);
	D3DXPlaneFromPoints(&m_arrPlane[PBack], &m_arrBox[BRT], &m_arrBox[BLT], &m_arrBox[BRB]);
	D3DXPlaneFromPoints(&m_arrPlane[PLeft], &m_arrBox[BLT], &m_arrBox[FLT], &m_arrBox[BLB]);
	D3DXPlaneFromPoints(&m_arrPlane[PRight], &m_arrBox[FRT], &m_arrBox[BRT], &m_arrBox[FRB]);
	D3DXPlaneFromPoints(&m_arrPlane[PUp], &m_arrBox[BLT], &m_arrBox[BRT], &m_arrBox[FLT]);
	D3DXPlaneFromPoints(&m_arrPlane[PDown], &m_arrBox[FLB], &m_arrBox[FRB], &m_arrBox[BLB]);
}

bool cCamera::IsIn(ST_SPHERE * sphere)
{
	for (int i = 0; i < 6; i++)
	{
		if (D3DXPlaneDotCoord(&m_arrPlane[i], &sphere->vCenter) >= sphere->fRadius)
			return false;
	}
	return true;
}
