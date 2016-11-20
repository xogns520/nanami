#pragma once

class cCamera
{
private:
	D3DXVECTOR3		m_vEye;
	D3DXVECTOR3		m_vLookAt;
	D3DXVECTOR3		m_vUp;
	bool			m_isLButtonDown;
	POINT			m_ptPrevMouse;
	float			m_fAngleX;
	float			m_fAngleY;
	float			m_fDistance;

	D3DXPLANE		m_arrPlane[6];
	D3DXVECTOR3     m_arrBox[8];
public:
	cCamera(void);
	~cCamera(void);

	void Setup();
	void Update(D3DXVECTOR3* pTarget = NULL);
	void Update(float Angle, D3DXVECTOR3* pTarget = NULL);
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	D3DXVECTOR3 GetEye() { return m_vEye; }

	void FrustumUpdate();
	bool IsIn(ST_SPHERE* sphere);
};

