#include "stdafx.h"
#include "cEffect.h"
#include "cGroup.h"


cEffect::cEffect()
	: m_filePath("")
	, m_bIsOn(false)
	, m_fAnimationSpeed(0.f)
	, m_fAlpha(0.f)
	, m_bIsSprite(false)
	, m_pSprite(NULL)
	, m_pMesh(NULL)
	, m_centerPosition(0, 0, 0)
	, m_worldTime(0)
{
	D3DXMatrixIdentity(&m_matWorld);
	m_centerPosition = D3DXVECTOR3(0, 0, 0);	//임시
}


cEffect::~cEffect()
{

}


void cEffect::Destroy()
{
	SAFE_RELEASE(m_pSprite);
}


void cEffect::Setup(char* path, float size, float animationSpeed, float alpha)
{
	m_bIsSprite = true;
	m_fSpriteSize = size;

	//스프라이트로 로딩하는 경우
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	D3DXIMAGE_INFO stImageInfo;
	m_pSpriteTexture = g_pTextureManager->GetTexture(path, &stImageInfo);
	SetRect(&m_rSpriteRect, 0, 0, stImageInfo.Width, stImageInfo.Height);
}


void cEffect::Setup(char* path, char* shaderPath) 
{
	m_bIsSprite = false;

	//메쉬로 로딩하는 경우
	cObjLoader* l = new cObjLoader;
	bool isUvFlip = true;

	l->Load(path, m_vecObj, isUvFlip, &m_matWorld);

	//void cObjLoader::Load(IN char* szFilename, OUT std::vector<cGroup*>& vecGroup, IN bool isUvFlip, IN D3DXMATRIXA16* pmat)
	//m_pMesh = l->Load(path, m_vecMeshMtlTex, isUvFlip, &m_matWorld);
	
	m_pEffect = LoadEffect(shaderPath);
}


LPD3DXEFFECT cEffect::LoadEffect(const char* szFileName)
{
	LPD3DXEFFECT pEffect = NULL;

	// 셰이더 로딩
	LPD3DXBUFFER		pError = NULL;			//에러 버퍼 ( 셰이더를 컴파일할때 잘못 된 문법이나 오류정보를 리턴해주는 버퍼 )
	DWORD				dwShaderFlag = 0;		//셰이더 플레그 0 

#ifdef _DEBUG
	dwShaderFlag = dwShaderFlag | D3DXSHADER_DEBUG;		//셰이더를 디버그모드로 컴파일하겠다 ( 디버그모드로 해야 잘못된 컴파일 오류가 날때 Error 버퍼에 오류정보가 들어간다 ) 
#endif

	//fx 파일로 부터 셰이더 객체 생성
	D3DXCreateEffectFromFile(
		g_pD3DDevice,				// 디바이스
		szFileName,					// 불러올 셰이더 코드 파일이름
		NULL,						// 셰이더를 컴파일할때 추가로 사용할 #define 정의 ( 일단 NULL )
		NULL,						// 셰이더를 컴파일할때 #include 지시문을 처리할때 사용할 인터페이스 플레그 ( 일단 NULL )
		dwShaderFlag,				// 셰이더 컴파일 플레그
		NULL,						// 셰이더 매개변수를 공유할 메모리풀 ( 일단 NULL )
		&pEffect,					// 로딩될 셰이더 Effect 포인터
		&pError						// 셰이더를 로딩하고 컴파일할때 문제가 생기면 해당 버퍼에 에러메시지가 들어간다 ( 성공적으로 로딩되면 NULL 이 참조된다 )
		);

	//셰이더 파일로딩에문재가 있다면..
	if (pError != NULL || pEffect == NULL){

		//문제의 내용이 뭔지 문자열로 확인
		int size = pError->GetBufferSize();
		char* str = new char[size];

		//str에 버퍼에있는 내용을 저장한다.
		sprintf_s(str, size, (const char*)pError->GetBufferPointer());

		OutputDebugString(str);
		//오류내용을 출력했으니 오류버퍼 해제
		SAFE_RELEASE(pError);
		if (str)
		{
			delete[] str;
		}

		return NULL;
	}

	return pEffect;
}

void cEffect::Update()
{
	m_worldTime++;
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
		

		// 텍스쳐 알파 옵션 설정
		g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
		g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

		// 알파블랜딩 방식 결정.
		g_pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

		
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
		//쉐이더 추가 예정 -- TEST중!!
		//m_matWorld;
		D3DXMATRIXA16 matWorld, matView, matProjection;
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixTranslation(&matWorld, m_centerPosition.x, m_centerPosition.y, m_centerPosition.z);
		g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
		g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProjection);

		m_pEffect->SetMatrix("matWorld", &matWorld);
		m_pEffect->SetMatrix("matView", &matView);
		m_pEffect->SetMatrix("matProjection", &matProjection);
		
		m_pEffect->SetFloat("fTime", m_worldTime/10);
		
		UINT numPasses = 0;
		m_pEffect->Begin(&numPasses, NULL);

		for (UINT i = 0; i < numPasses; ++i)
		{
			m_pEffect->BeginPass(i);
		
			for each(auto p in m_vecObj)
			{
				p->Render();
			}
		
			m_pEffect->EndPass();
		}

		m_pEffect->End();
		g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
		g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	}


}


