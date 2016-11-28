#include "stdafx.h"
#include "cEffect.h"




cEffect::cEffect()
: m_filePath("")
, m_bIsOn(false)
, m_fAnimationSpeed(0.f)
, m_fAlpha(0.f)
, m_bIsSprite(false)
, m_pSprite(NULL)
, m_pMesh(NULL)
, m_centerPosition(0, 0, 0)
{
}


cEffect::~cEffect()
{
}


void cEffect::Destroy()
{
	SAFE_RELEASE(m_pSprite);
}


void cEffect::Setup(char* path, bool isSprite, float animationSpeed, float alpha)
{
	D3DXMatrixIdentity(&m_matWorld);

	m_bIsSprite = isSprite;

	m_centerPosition = D3DXVECTOR3(0, 0, 0);	//임시

	if (isSprite) {
		//스프라이트로 로딩하는 경우
		D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

		D3DXIMAGE_INFO stImageInfo;
		m_pSpriteTexture = g_pTextureManager->GetTexture(path, &stImageInfo);
		SetRect(&m_rSpriteRect, 0, 0, stImageInfo.Width, stImageInfo.Height);
	}
	else {
		//메쉬로 로딩하는 경우
		cObjLoader* l = new cObjLoader;
		bool isUvFlip = true;
		m_pMesh = l->Load(path, m_vecMeshMtlTex, isUvFlip, &m_matWorld);
	}
}


void cEffect::Render()
{
	if (m_bIsSprite) {
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
		g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		g_pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
		
		//worldmatrix적용하는부분 확인해야함!!
		
		D3DXMATRIXA16 matWorld, matView, matProj, matS;
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixScaling(&matS, 0.2, 0.2, 0.2);
		m_pSprite->SetTransform(&matS);
		
		g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
		g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);
		
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		
		D3DXVec3TransformCoord(&m_centerPosition, &m_centerPosition, &matView);
		D3DXVec3TransformCoord(&m_centerPosition, &m_centerPosition, &matView);
		
		RECT rc;
		GetClientRect(g_hWnd, &rc);
		
		/*
		
		var viewProj = mMainCamera.View * mMainCamera.Projection;
		var vp = mDevice.ImmediateContext.Rasterizer.GetViewports()[0];
		var screenCoords = Vector3.Project(worldSpaceCoordinates, vp.X, vp.Y, vp.Width, vp.Height, vp.MinZ, vp.MaxZ, viewProj);
		*/
		
		D3DVIEWPORT9 vp;
		//D3DXVECTOR3 pos = 
		
		
		//D3DXVECTOR3 pos = D3DXVECTOR3(
		//	(0.5 * (m_centerPosition.x + 1) * m_rSpriteRect.right - m_rSpriteRect.left),
		//	(0.5 * (m_centerPosition.y + 1) * m_rSpriteRect.bottom - m_rSpriteRect.top),
		//	0);
		
		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
		m_pSprite->Draw(m_pSpriteTexture,
			//&m_rSpriteRect,
			NULL,
			NULL,
			&D3DXVECTOR3(0, 0, 0),
			//&pos,
			D3DCOLOR_RGBA(255, 255, 255, 255));
		m_pSprite->End();
		
		g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
		g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		//g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	}
	else {
		//쉐이더 추가 예정


	}


}


//void cEffect::SetSpriteSize(D3DXMATRIXA16 mat) {
//
//
//}