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


void cEffect::Setup(char* path, bool isSprite, float size, float animationSpeed, float alpha)
{
	D3DXMatrixIdentity(&m_matWorld);

	m_bIsSprite = isSprite;
	m_fSpriteSize = size;

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
		//파티클 이용!!
		
		//----------------------------------------------------------------------
		// 포인트를 확대 축소 할 수 있게 해줌
		g_pD3DDevice->SetRenderState(D3DRS_POINTSCALEENABLE, true);
		// 포인트 스케일링 Factor값 설정
		g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_A, FtoDw(0.0f));
		g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_B, FtoDw(0.0f));
		g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_C, FtoDw(1.0f));

		// 포인트에 텍스쳐를 입힐 수 있게 해줌
		g_pD3DDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
		
		// 텍스쳐 알파 옵션 설정
		g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
		g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

		// 알파블랜딩 방식 결정.
		g_pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

		// 포인트 최소 크기
		g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE_MIN, FtoDw(1.0f));
		// 포인트 최대 크기
		g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE_MAX, FtoDw(1000.0f));
		// 포인트 사이즈 설정
		g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE, FtoDw(m_fSpriteSize));
		//----------------------------------------------------------------------

		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
		g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
		
		D3DXMATRIXA16 matWorld;
		D3DXMatrixIdentity(&matWorld);
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

		g_pD3DDevice->SetTexture(0, m_pSpriteTexture);
		g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);

		std::vector<ST_PC_VERTEX> t;
		ST_PC_VERTEX temp;
		temp.p = m_centerPosition;
		temp.c = D3DCOLOR_ARGB(255, 255, 255, 255);
		t.push_back(temp);

		g_pD3DDevice->DrawPrimitiveUP(D3DPT_POINTLIST,
			t.size(),
			&t[0],
			sizeof(ST_PC_VERTEX));

		g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
		g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		//g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	}
	else {
		//쉐이더 추가 예정


	}


}


