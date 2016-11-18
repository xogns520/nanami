#include "stdafx.h"
#include "cTerrain.h"
#include "cMtlTex.h"


cTerrain::cTerrain()
: m_pMesh(nullptr)
, m_pMtlTex(nullptr)
, m_fBrightness(0.5f)
, m_vStart(0, 0, 0)
, m_vEnd(0, 0, 0)
, m_vCurrent(0, -1, 0)
, m_ft(0)
, m_fHeightRadio(0.05f)
{
	//if (m_pMtlTex)
	//	SAFE_RELEASE(m_pMtlTex->pTex);
}

cTerrain::~cTerrain()
{
	SAFE_RELEASE(m_pMesh);
	if (m_pMtlTex){ SAFE_RELEASE(m_pMtlTex); }
	for (size_t i = 0; i < m_vecvecVertex.size(); ++i){ m_vecvecVertex[i].clear(); }
}
void cTerrain::Setup()
{
	//메쉬 구성
	BuildMesh(m_vecVertex);

	//머테리얼
	m_pMtlTex = new cMtlTex;
	m_pMtlTex->AddRef();
	ZeroMemory(&m_pMtlTex->GetMtl(), sizeof(m_pMtlTex->GetMtl()));
	m_pMtlTex->GetMtl().Ambient = D3DXCOLOR(1.f, 1.f, 1.f, 1.f)*m_fBrightness;
	m_pMtlTex->GetMtl().Diffuse = D3DXCOLOR(1.f, 1.f, 1.f, 1.f)*m_fBrightness;
	m_pMtlTex->GetMtl().Specular = D3DXCOLOR(1.f, 1.f, 1.f, 1.f)*m_fBrightness;
	string sTexturePath = string(RESOURCE_FOLDER) + string("HeightMapData/") + string("Terrain1map.jpg");
	//strcpy(destination, source)
	m_pMtlTex->SetTexture(g_pTextureManager->GetTexture(sTexturePath)); //★

}
void cTerrain::Update()
{
	//if (m_fBrightness < 0){ m_fBrightness += 1.f; }
	m_pMtlTex->GetMtl().Ambient = D3DXCOLOR(1.f, 1.f, 1.f, 1.f)*m_fBrightness;
	m_pMtlTex->GetMtl().Diffuse = D3DXCOLOR(1.f, 1.f, 1.f, 1.f)*m_fBrightness;
	m_pMtlTex->GetMtl().Specular = D3DXCOLOR(1.f, 1.f, 1.f, 1.f)*m_fBrightness;
	for (int i = 0; i < m_vecVertex.size(); ++i)
	{
		static int a = 0;
		a++;
	}

}


void cTerrain::Render()
{


	//g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	//g_pD3DDevice->LightEnable(0, true);
	if (m_pMtlTex)
	{
		g_pD3DDevice->SetMaterial(&m_pMtlTex->GetMtl());
		g_pD3DDevice->SetTexture(0, m_pMtlTex->GetTexture());
	}

	if (m_pMesh)
		m_pMesh->DrawSubset(0);

	g_pD3DDevice->SetTexture(0, nullptr);
	//g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}
float cTerrain::GetHeight(const D3DXVECTOR3& vPos)
{
	float ret = 0;
	if (m_vecvecVertex.empty())
	{
		m_vecvecVertex.reserve((ROOM_LENGTH + 1)*(ROOM_LENGTH + 1));
		for (size_t i = 0; i < ROOM_LENGTH + 1; ++i)
		{
			vector<D3DXVECTOR3> vec;
			vec.resize(ROOM_LENGTH + 1);
			m_vecvecVertex.push_back(vec);
		}

		for (size_t z = 0; z <= ROOM_LENGTH; ++z)
		{
			for (size_t x = 0; x <= ROOM_LENGTH; ++x)
			{
				D3DXVECTOR3 v = m_vecVertex[z*(ROOM_LENGTH + 1) + x].p;
				m_vecvecVertex[z][x] = v;
			}
		}
	}
	//벡터 인덱스역할. 좌하단 인덱스가 나오게 된다.
	float x = floorf(vPos.x);
	float z = floorf(vPos.z);

	//A-B
	//|\|
	//C-D

	D3DXVECTOR3 vA = m_vecvecVertex[z + 1][x];
	D3DXVECTOR3 vB = m_vecvecVertex[z + 1][x + 1];
	D3DXVECTOR3 vC = m_vecvecVertex[z][x];
	D3DXVECTOR3 vD = m_vecvecVertex[z][x + 1];

	D3DXVECTOR3 vDU = vA - vC;
	D3DXVECTOR3 vLR = vD - vC;
	D3DXVECTOR3 vRL = vA - vB;
	D3DXVECTOR3 vUD = vD - vB;

	float fTempZ = (vPos.z - vC.z) / vDU.z;
	float fTempX = (vPos.x - vC.x) / vLR.x;

	//윗면인지 아랫면인지
	bool isDown = false;

	if (fTempZ + fTempX <= 1)
	{
		isDown = true;
	}
	else { isDown = false; }

	if (isDown == true)
	{
		D3DXVECTOR3 vH = (vDU*fTempZ);
		D3DXVECTOR3 vW = (vLR*fTempX);

		ret = ((vH + vW) + vC).y;
	}
	else if (isDown == false)
	{
		fTempZ = (vPos.z - vB.z) / vUD.z;
		fTempX = (vPos.x - vB.x) / vRL.x;
		D3DXVECTOR3 vH = (vUD*fTempZ);
		D3DXVECTOR3 vW = (vRL*fTempX);

		ret = ((vH + vW) + vB).y;
	}

	return ret;
}
void cTerrain::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYDOWN:
		if (wParam == VK_F1 && m_fBrightness<1.f) { m_fBrightness += 0.02f; }
		if (wParam == VK_F2 && m_fBrightness > 0.15f) { m_fBrightness -= 0.02f; }
		if (wParam == VK_F3)
		{
			D3DLIGHT9 stLight;
			ZeroMemory(&stLight, sizeof(D3DLIGHT9));
			stLight.Type = D3DLIGHT_DIRECTIONAL;
			D3DXVECTOR3 vDir = m_vecVertex.front().p;
			D3DXVec3Normalize(&vDir, &vDir);
			stLight.Direction = vDir;
			stLight.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
			stLight.Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
			stLight.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
			g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
		}	//
		if (wParam == VK_F4)
		{
			//보간과 회전으로 일출과 일몰을 해볼수도 있었겠다. 아쉽지만 내일을 위해 자자
			D3DLIGHT9 stLight;
			ZeroMemory(&stLight, sizeof(D3DLIGHT9));
			stLight.Type = D3DLIGHT_DIRECTIONAL;
			D3DXVECTOR3 vDir;
			D3DXVec3Lerp(&vDir, &m_vecVertex.front().p, &m_vecVertex.back().p, m_ft);
			m_ft++;
			D3DXVec3Normalize(&vDir, &vDir);
			stLight.Direction = vDir;
			stLight.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
			stLight.Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
			stLight.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
			g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
		}
	default:
		break;
	}
	return;
}

void cTerrain::BuildMesh(vector<ST_PNT_VERTEX>& vecVertex)
{
	ST_PNT_VERTEX vPNT;
	vPNT.n = D3DXVECTOR3(0, 0, 0);
	vPNT.p = D3DXVECTOR3(0, 0, 0);
	vPNT.t = D3DXVECTOR2(0, 0);

	//메쉬에 필요한 벡터 입력

	//버텍스
	m_vecV.clear();
	vecVertex.clear();
	D3DXVECTOR3 v3;
	size_t fHeigthNum = 0;

	for (size_t i = 0; i < ROOM_LENGTH + 1; ++i)
	{
		for (size_t j = 0; j < ROOM_LENGTH + 1; ++j)
		{
			v3 = D3DXVECTOR3((float)j, m_vecHeight[fHeigthNum++] * m_fHeightRadio, (float)i);
			//m_vecV.push_back(v3);
			vPNT.p = v3;//D3DXVECTOR3(v3.x-10, v3.y, v3.z-10);
			vPNT.t.x = ((float)j / ROOM_LENGTH + 1);
			vPNT.t.y = ((float)i / ROOM_LENGTH + 1);
			vecVertex.push_back(vPNT);
		}
	}
	//인덱스
	m_vecI.clear();
	int nVertexNum = -1;
	int nCnt = 0;
	for (size_t i = 0; i < ROOM_LENGTH; ++i)
	{
		for (size_t j = 0; j < ROOM_LENGTH; j++)
		{
			//좌하단
			m_vecI.push_back(((ROOM_LENGTH + 1)*i) + (ROOM_LENGTH + 1) + j);
			m_vecI.push_back(((ROOM_LENGTH + 1)*i) + j + 1);
			m_vecI.push_back(((ROOM_LENGTH + 1)*i) + j);
			//우상단
			m_vecI.push_back(((ROOM_LENGTH + 1)*i) + (ROOM_LENGTH + 1) + j);
			m_vecI.push_back(((ROOM_LENGTH + 1)*i) + (ROOM_LENGTH + 1) + j + 1);
			m_vecI.push_back(((ROOM_LENGTH + 1)*i) + j + 1);
		}
	}
	//노멀 계산용 2차원 벡터
	vector<vector<D3DXVECTOR3>> vecvec;
	for (size_t i = 0; i < ROOM_LENGTH + 1; ++i)
	{
		vector<D3DXVECTOR3> vec;
		vec.resize(ROOM_LENGTH + 1);
		vecvec.push_back(vec);
	}
	for (size_t i = 0; i < ROOM_LENGTH + 1; ++i)
	{
		for (size_t j = 0; j < ROOM_LENGTH + 1; ++j)
		{
			if (j == 0 || j == ROOM_LENGTH ||
				i == 0 || i == ROOM_LENGTH)
			{
				vecvec[i][j] = D3DXVECTOR3(10, 0, 10);
			}
			else
			{
				D3DXVECTOR3 vx1 = m_vecVertex[(ROOM_LENGTH + 1)*i + (j - 1)].p;
				D3DXVECTOR3 vx2 = m_vecVertex[(ROOM_LENGTH + 1)*i + (j + 1)].p;
				D3DXVECTOR3 vz1 = m_vecVertex[(ROOM_LENGTH + 1)*(i + 1) + j].p;
				D3DXVECTOR3 vz2 = m_vecVertex[(ROOM_LENGTH + 1)*(i - 1) + j].p;

				D3DXVec3Cross(&vecvec[i][j], &(vx2 - vx1), &(vz2 - vz1));
			}

			D3DXVec3Normalize(&vecvec[i][j], &vecvec[i][j]);
			vecVertex[((ROOM_LENGTH + 1)*i) + j].n = vecvec[i][j];
		}
	}
	//2차원 벡터 해제
	for (size_t i = 0; i < vecvec.size(); ++i){ vecvec[i].clear(); }
	vecvec.clear();

	//메쉬 구성 시작
	HRESULT hr = D3DXCreateMeshFVF(m_vecI.size() / 3,
		vecVertex.size(),
		D3DXMESH_32BIT | D3DXMESH_MANAGED,
		ST_PNT_VERTEX::FVF,
		g_pD3DDevice,
		&m_pMesh);

	assert(m_pMesh != nullptr);

	//버텍스 버퍼
	ST_PNT_VERTEX* pV = NULL;
	m_pMesh->LockVertexBuffer(0, (LPVOID*)&pV);
	memcpy(pV, &vecVertex[0], vecVertex.size()*sizeof(ST_PNT_VERTEX));
	m_pMesh->UnlockVertexBuffer();

	//인덱스 버퍼
	DWORD* pI = nullptr;
	m_pMesh->LockIndexBuffer(0, (LPVOID*)&pI);
	memcpy(pI, &m_vecI[0], m_vecI.size()*sizeof(DWORD));
	m_pMesh->UnlockIndexBuffer();

	//
	//g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//D3DXMATRIXA16 matT;
	//D3DXMatrixTranslation(&matT, -128, 0, -128);
	//g_pD3DDevice->SetTransform(D3DTS_WORLD, &matT);

}