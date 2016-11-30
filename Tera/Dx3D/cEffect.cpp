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
	m_centerPosition = D3DXVECTOR3(0, 0, 0);	//�ӽ�
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

	//��������Ʈ�� �ε��ϴ� ���
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	D3DXIMAGE_INFO stImageInfo;
	m_pSpriteTexture = g_pTextureManager->GetTexture(path, &stImageInfo);
	SetRect(&m_rSpriteRect, 0, 0, stImageInfo.Width, stImageInfo.Height);
}


void cEffect::Setup(char* path, char* shaderPath) 
{
	m_bIsSprite = false;

	//�޽��� �ε��ϴ� ���
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

	// ���̴� �ε�
	LPD3DXBUFFER		pError = NULL;			//���� ���� ( ���̴��� �������Ҷ� �߸� �� �����̳� ���������� �������ִ� ���� )
	DWORD				dwShaderFlag = 0;		//���̴� �÷��� 0 

#ifdef _DEBUG
	dwShaderFlag = dwShaderFlag | D3DXSHADER_DEBUG;		//���̴��� ����׸��� �������ϰڴ� ( ����׸��� �ؾ� �߸��� ������ ������ ���� Error ���ۿ� ���������� ���� ) 
#endif

	//fx ���Ϸ� ���� ���̴� ��ü ����
	D3DXCreateEffectFromFile(
		g_pD3DDevice,				// ����̽�
		szFileName,					// �ҷ��� ���̴� �ڵ� �����̸�
		NULL,						// ���̴��� �������Ҷ� �߰��� ����� #define ���� ( �ϴ� NULL )
		NULL,						// ���̴��� �������Ҷ� #include ���ù��� ó���Ҷ� ����� �������̽� �÷��� ( �ϴ� NULL )
		dwShaderFlag,				// ���̴� ������ �÷���
		NULL,						// ���̴� �Ű������� ������ �޸�Ǯ ( �ϴ� NULL )
		&pEffect,					// �ε��� ���̴� Effect ������
		&pError						// ���̴��� �ε��ϰ� �������Ҷ� ������ ����� �ش� ���ۿ� �����޽����� ���� ( ���������� �ε��Ǹ� NULL �� �����ȴ� )
		);

	//���̴� ���Ϸε������簡 �ִٸ�..
	if (pError != NULL || pEffect == NULL){

		//������ ������ ���� ���ڿ��� Ȯ��
		int size = pError->GetBufferSize();
		char* str = new char[size];

		//str�� ���ۿ��ִ� ������ �����Ѵ�.
		sprintf_s(str, size, (const char*)pError->GetBufferPointer());

		OutputDebugString(str);
		//���������� ��������� �������� ����
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
		//��ƼŬ �̿�!!
		
		//----------------------------------------------------------------------
		// ����Ʈ�� Ȯ�� ��� �� �� �ְ� ����
		g_pD3DDevice->SetRenderState(D3DRS_POINTSCALEENABLE, true);
		// ����Ʈ �����ϸ� Factor�� ����
		g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_A, FtoDw(0.0f));
		g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_B, FtoDw(0.0f));
		g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_C, FtoDw(1.0f));

		// ����Ʈ�� �ؽ��ĸ� ���� �� �ְ� ����
		g_pD3DDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
		
		// �ؽ��� ���� �ɼ� ����
		g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
		g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

		// ���ĺ��� ��� ����.
		g_pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

		// ����Ʈ �ּ� ũ��
		g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE_MIN, FtoDw(1.0f));
		// ����Ʈ �ִ� ũ��
		g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE_MAX, FtoDw(1000.0f));
		// ����Ʈ ������ ����
		g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE, FtoDw(m_fSpriteSize));
		//----------------------------------------------------------------------

		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
		g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
		

		// �ؽ��� ���� �ɼ� ����
		g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
		g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

		// ���ĺ��� ��� ����.
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
		//���̴� �߰� ���� -- TEST��!!
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


