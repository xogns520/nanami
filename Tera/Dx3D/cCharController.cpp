#include "StdAfx.h"
#include "cCharController.h"
#include "iMap.h"
#include "cMapSkinnedMesh.h"
#include "cPlayer.h"

cCharController::cCharController(void)
	: m_vPosition(0, 0, 0)
	, m_vDirection(0, 0, 1)
	, m_fAngle(0.0f)
	, m_fSpeed(0.25f)
	, m_bAtt(false)
	, m_state(Pempty)
	//, m_nMoveKey(false)
{
	D3DXMatrixIdentity(&m_matWorld);
}

cCharController::~cCharController(void)
{
}

void cCharController::Update(iMap* pMap)
{
	if (GetKeyState('A') & 0x8000)
	{
		m_fAngle -= 0.1f;
	}
	if (GetKeyState('D') & 0x8000)
	{
		m_fAngle += 0.1f;
	}

	m_vDirection = D3DXVECTOR3(0, 0, 1);
	D3DXMATRIXA16 matRotY;
	D3DXMatrixRotationY(&matRotY, m_fAngle);
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matRotY);

	D3DXVECTOR3 p = m_vPosition;
	if (GetKeyState('W') & 0x8000)
	{
		p = p + m_vDirection * m_fSpeed;
		m_nMoveKey = 0;
	}
	if (GetKeyState('S') & 0x8000)
	{
		p = p - m_vDirection * m_fSpeed;
		m_nMoveKey = 0;
	}
	
	if (!(GetKeyState('W') & 0x8000) && !(GetKeyState('S') & 0x8000))
	{
		m_nMoveKey = 1;
	}

	if(pMap && pMap->GetHeight(p.x, p.y, p.z))
	{
		m_vPosition = p;
	}

	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = matRotY * matT;
// 
// 
// 	D3DLIGHT9 stLight;
// 	stLight.Ambient = stLight.Diffuse = stLight.Specular = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
// 	stLight.Type = D3DLIGHT_SPOT;
// 	D3DXVECTOR3 vDir;
// 	D3DXVec3Normalize(&vDir, &m_vDirection);
// 	stLight.Direction = vDir;
// 	stLight.Position = m_vPosition;
// 	stLight.Theta = D3DX_PI / 8;
// 	stLight.Phi = D3DX_PI / 6;
// 	stLight.Range = 100.f;
// 	g_pD3DDevice->SetLight(1, &stLight);
// 	g_pD3DDevice->LightEnable(1, true);
}

void cCharController::Update(cMapSkinnedMesh* pMap)
{
	if (GetKeyState('A') & 0x8000)
	{
		m_fAngle -= 0.1f;
	}
	if (GetKeyState('D') & 0x8000)
	{
		m_fAngle += 0.1f;
	}

	m_vDirection = D3DXVECTOR3(0, 0, 1);
	D3DXMATRIXA16 matRotY;
	D3DXMatrixRotationY(&matRotY, m_fAngle);
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matRotY);

	D3DXVECTOR3 p = m_vPosition;
	if (GetKeyState('W') & 0x8000)
	{
		p = p + m_vDirection * m_fSpeed;
		m_nMoveKey = 0;
	}
	if (GetKeyState('S') & 0x8000)
	{
		p = p - m_vDirection * m_fSpeed;
		m_nMoveKey = 0;
	}

	if (!(GetKeyState('W') & 0x8000) && !(GetKeyState('S') & 0x8000))
	{
		m_nMoveKey = 1;
	}

	if (pMap && pMap->GetHeight(p.x, p.y, p.z))
	{
		m_vPosition = p;
	}

	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = matRotY * matT;
	// 
	// 
	// 	D3DLIGHT9 stLight;
	// 	stLight.Ambient = stLight.Diffuse = stLight.Specular = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
	// 	stLight.Type = D3DLIGHT_SPOT;
	// 	D3DXVECTOR3 vDir;
	// 	D3DXVec3Normalize(&vDir, &m_vDirection);
	// 	stLight.Direction = vDir;
	// 	stLight.Position = m_vPosition;
	// 	stLight.Theta = D3DX_PI / 8;
	// 	stLight.Phi = D3DX_PI / 6;
	// 	stLight.Range = 100.f;
	// 	g_pD3DDevice->SetLight(1, &stLight);
	// 	g_pD3DDevice->LightEnable(1, true);
}

void cCharController::Update(cMapSkinnedMesh * pMap, cPlayer * pPlayer)
{
	if (GetKeyState('A') & 0x8000)
	{
		m_fAngle -= 0.1f;
	}
	if (GetKeyState('D') & 0x8000)
	{
		m_fAngle += 0.1f;
	}

	m_vDirection = D3DXVECTOR3(0, 0, 1);
	D3DXMATRIXA16 matRotY;
	D3DXMatrixRotationY(&matRotY, m_fAngle);
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matRotY);

	D3DXVECTOR3 p = m_vPosition;
	//if (GetKeyState('W') & 0x8000)
	if (!m_bAtt)
	{
		if (g_pKeyManager->isStayKeyDown('W'))
		{
			p = p + m_vDirection * m_fSpeed;
			if (m_state != run)
			{
				pPlayer->Update(4);
				m_state = run;
			}
		}
		if (g_pKeyManager->isStayKeyDown('S'))
		{
			p = p - m_vDirection * m_fSpeed;
			if (m_state != run)
			{
				pPlayer->Update(4);
				m_state = run;
			}
		}
	}

	if (g_pKeyManager->isOnceKeyDown('L'))
	{
		m_bAtt = true;
		if (m_nMoveKey > 3)
		{
			m_state = attack;
			pPlayer->Update(3);
			m_nMoveKey = 3;
		}
		else
		{
			if (m_nMoveKey > -1)
				pPlayer->Update(--m_nMoveKey);
		}
	}
	// 0.01~0.005

	if (m_state != idle && !GetAsyncKeyState('W'))
	{
		if (!m_bAtt)
		{
			pPlayer->Update(5);
			m_nMoveKey = 4;
			m_state = idle;
		}
		else
		{
			if (m_nMoveKey == -1)
			{
				m_bAtt = false;
				m_nMoveKey = 4;
			}
		}

	}

	if (pMap && pMap->GetHeight(p.x, p.y, p.z))
	{
		m_vPosition = p;
	}

	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = matRotY * matT;
}
