#include "StdAfx.h"
#include "cWeapon.h"
#include "cObjLoader.h"
#include "cGroup.h"

cWeapon::cWeapon(void)
{
}


cWeapon::~cWeapon(void)
{
	for each(auto p in m_vecGroup)
	{
		SAFE_DELETE(p);
	}
}

void cWeapon::Load(char* szMap, char* szSurface, D3DXMATRIXA16* pmat)
{
	cObjLoader l;
	bool isFlipUv = true;		//20161122 UV Flip여부 추가
	l.Load(szMap, m_vecGroup, isFlipUv);

	std::vector<D3DXVECTOR3> vecV;

	FILE* fp = NULL;
	fopen_s(&fp, szSurface, "r");
	while (!feof(fp))
	{
		char szBuf[1024] = { '\0', };

		fgets(szBuf, 1024, fp);

		if (strlen(szBuf) == 0)
			continue;

		if (szBuf[0] == '#')
		{
			continue;
		}
		else if (szBuf[0] == 'v' && szBuf[1] < 33)
		{
			float x, y, z;
			sscanf_s(szBuf, "%*s %f %f %f", &x, &y, &z);
			vecV.push_back(D3DXVECTOR3(x, y, z));
		}
		else if (szBuf[0] == 'f')
		{
			int aIndex[3];
			sscanf_s(szBuf, "%*s %d/%*d/%*d %d/%*d/%*d %d/%*d/%*d",
				&aIndex[0], &aIndex[1], &aIndex[2]);

			for (int i = 0; i < 3; ++i)
			{
				D3DXVECTOR3 p = vecV[aIndex[i] - 1];
				if (pmat)
				{
					D3DXVec3TransformCoord(&p, &p, pmat);
				}
				m_vecSurface.push_back(p);
			}
		}
	}
	fclose(fp);
}

void cWeapon::Load(char* szMap, D3DXMATRIXA16* pmat)
{
	cObjLoader l;
	bool isFlipUv = true;		//20161122 UV Flip여부 추가l.Load(szMap, m_vecGroup, isFlipUv);}
	l.Load(szMap, m_vecGroup, isFlipUv ,pmat);

	//m_Sphere.vCenter = D3DXVECTOR3(0.0f, 0.75f, 0.0f);
	m_Sphere.fRadius = 0.2f;

	D3DXCreateSphere(g_pD3DDevice, m_Sphere.fRadius, 20, 20, &m_pSphere, NULL);
	m_Color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	
}

bool cWeapon::GetHeight(IN float x, OUT float& y, IN float z)
{
	D3DXVECTOR3 vRayPos(x, 1000, z);
	D3DXVECTOR3 vRayDir(0, -1, 0);

	for (size_t i = 0; i < m_vecSurface.size(); i += 3)
	{
		float u, v, d;
		if (D3DXIntersectTri(&m_vecSurface[i + 0],
			&m_vecSurface[i + 1],
			&m_vecSurface[i + 2],
			&vRayPos,
			&vRayDir,
			&u, &v, &d))
		{
			y = 1000 - d;
			return true;
		}
	}
	return false;
}

void cWeapon::Render()
{
	//2016.11.13 - WIJY 
	//Scaling 삭제
	D3DXMATRIXA16 mat, matT, matS;
	//D3DXMatrixIdentity(&mat);
	//D3DXMatrixScaling(&matS, 0.1f, 0.1f, 0.1f);
	D3DXMatrixTranslation(&matT, -5.0, 0, 0);
	mat = matT;

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	for each(auto p in m_vecGroup)
	{
		p->Render();
	}
}

void cWeapon::Render(D3DXMATRIX * pMat)
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, pMat);

	for each(auto p in m_vecGroup)
	{
		p->Render();
	}

	if (m_pSphere)
	{
		D3DXMATRIXA16 matY, mat;
		D3DXMatrixIdentity(&matY);
		D3DXMatrixTranslation(&matY, 0.0f, 0.75f, 0.0f);

		mat = matY * *pMat;

		m_Sphere.vCenter = D3DXVECTOR3(mat._41, mat._42, mat._43);

		D3DMATERIAL9 stMtl;
		ZeroMemory(&stMtl, sizeof(D3DMATERIAL9));

		stMtl.Ambient = stMtl.Diffuse = stMtl.Specular = m_Color;

		g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);
		//g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		g_pD3DDevice->SetMaterial(&stMtl);
		m_pSphere->DrawSubset(0);
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
	
}
