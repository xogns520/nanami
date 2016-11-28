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
		D3DXMATRIXA16 matWorld, matView, matInvView;

		g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
		D3DXMatrixInverse(&matInvView, 0, &matView);

		matWorld = matInvView;
		matWorld._41 = 0; matWorld._42 = 0; matWorld._43 = 0;
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

		//sprite 위치 계산
		//&m_centerPosition
		RECT rc;
		GetClientRect(g_hWnd, &rc);

		m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
		m_pSprite->Draw(m_pSpriteTexture,
			&m_rSpriteRect,
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(0, 0, 0),
			D3DCOLOR_XRGB(255, 255, 255));
		m_pSprite->End();

		g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
		g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	}
	else {
		//쉐이더 추가 예정


	}


}


void cEffect::SetSpriteSize(D3DXMATRIXA16 mat) {


}