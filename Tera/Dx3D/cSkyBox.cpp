#include "stdafx.h"
#include "cSkyBox.h"


cSkyBox::cSkyBox()
{
}


cSkyBox::~cSkyBox()
{
	SAFE_RELEASE(m_pVB);
	SAFE_DELETE(m_pTexture);
	delete[] m_pTex;
}

void cSkyBox::Setup(LPSTR lpTexFilename[6])
{

	for (int i = 0; i < 6; i++)
	{
		D3DXCreateTextureFromFile(g_pD3DDevice, lpTexFilename[i], &m_pTex[i]);
	}

	g_pD3DDevice->CreateVertexBuffer(24 * sizeof(ST_PT_VERTEX), 0, ST_PC_VERTEX::FVF, D3DPOOL_DEFAULT, &m_pVB, NULL);

	ST_PT_VERTEX vertices[24] =
	{
		{ ST_PT_VERTEX(D3DXVECTOR3(-1.f, 1.f, -1.f), D3DXVECTOR2(0.f, 0.f)) },
		{ ST_PT_VERTEX(D3DXVECTOR3(1.f, 1.f, -1.f), D3DXVECTOR2(1.f, 0.f)) },
		{ ST_PT_VERTEX(D3DXVECTOR3(-1.f, 1.f, 1.f), D3DXVECTOR2(0.f, 1.f)) },
		{ ST_PT_VERTEX(D3DXVECTOR3(1.f, 1.f, 1.f), D3DXVECTOR2(1.f, 1.f)) },

		{ ST_PT_VERTEX(D3DXVECTOR3(-1.f, 1.f, 1.f), D3DXVECTOR2(0.f, 0.f)) },
		{ ST_PT_VERTEX(D3DXVECTOR3(1.f, 1.f, 1.f), D3DXVECTOR2(1.f, 0.f)) },
		{ ST_PT_VERTEX(D3DXVECTOR3(-1.f, -1.f, 1.f), D3DXVECTOR2(0.f, 1.f)) },
		{ ST_PT_VERTEX(D3DXVECTOR3(1.f, -1.f, 1.f), D3DXVECTOR2(1.f, 1.f)) },

		{ ST_PT_VERTEX(D3DXVECTOR3(1.f, 1.f, -1.f), D3DXVECTOR2(0.f, 0.f)) },
		{ ST_PT_VERTEX(D3DXVECTOR3(-1.f, 1.f, -1.f), D3DXVECTOR2(1.f, 0.f)) },
		{ ST_PT_VERTEX(D3DXVECTOR3(1.f, -1.f, -1.f), D3DXVECTOR2(0.f, 1.f)) },
		{ ST_PT_VERTEX(D3DXVECTOR3(-1.f, -1.f, -1.f), D3DXVECTOR2(1.f, 1.f)) },

		{ ST_PT_VERTEX(D3DXVECTOR3(-1.f, 1.f, -1.f), D3DXVECTOR2(0.f, 0.f)) },
		{ ST_PT_VERTEX(D3DXVECTOR3(-1.f, 1.f, 1.f), D3DXVECTOR2(1.f, 0.f)) },
		{ ST_PT_VERTEX(D3DXVECTOR3(-1.f, -1.f, -1.f), D3DXVECTOR2(0.f, 1.f)) },
		{ ST_PT_VERTEX(D3DXVECTOR3(-1.f, -1.f, 1.f), D3DXVECTOR2(1.f, 1.f)) },

		{ ST_PT_VERTEX(D3DXVECTOR3(1.f, 1.f, 1.f), D3DXVECTOR2(0.f, 0.f)) },
		{ ST_PT_VERTEX(D3DXVECTOR3(1.f, 1.f, -1.f), D3DXVECTOR2(1.f, 0.f)) },
		{ ST_PT_VERTEX(D3DXVECTOR3(1.f, -1.f, 1.f), D3DXVECTOR2(0.f, 1.f)) },
		{ ST_PT_VERTEX(D3DXVECTOR3(1.f, -1.f, -1.f), D3DXVECTOR2(1.f, 1.f)) },

		{ ST_PT_VERTEX(D3DXVECTOR3(-1.f, -1.f, 1.f), D3DXVECTOR2(0.f, 0.f)) },
		{ ST_PT_VERTEX(D3DXVECTOR3(1.f, -1.f, 1.f), D3DXVECTOR2(1.f, 0.f)) },
		{ ST_PT_VERTEX(D3DXVECTOR3(-1.f, -1.f, -1.f), D3DXVECTOR2(0.f, 1.f)) },
		{ ST_PT_VERTEX(D3DXVECTOR3(1.f, -1.f, -1.f), D3DXVECTOR2(1.f, 1.f)) },
	};

	VOID* pVertices;
	m_pVB->Lock(0, 24 * sizeof(ST_PT_VERTEX), (void**)&pVertices, 0);

	memcpy(pVertices, vertices, 24 * sizeof(ST_PT_VERTEX));
	m_pVB->Unlock();


	D3DXMatrixScaling(&m_matScale, 100.f, 100.f, 100.f);
	m_matWorld = m_matScale;

}

void cSkyBox::Update()
{
}

void cSkyBox::Render(D3DXMATRIXA16* mat)
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, mat);

	//g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	//g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	//g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetFVF(ST_PT_VERTEX::FVF);
	g_pD3DDevice->SetStreamSource(0, m_pVB, 0, sizeof(ST_PT_VERTEX));
	
	for (int i = 0; i < 6; ++i)
	{
		g_pD3DDevice->SetTexture(0, m_pTex[i]);
		g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * 4, 2);

	}
	//g_pD3DDevice->DrawPrimitiveUP(
	//	D3DPT_TRIANGLELIST,
	//	m_vecVertex.size() / 3,
	//	&m_vecVertex[0],
	//	sizeof(ST_PT_VERTEX));
}