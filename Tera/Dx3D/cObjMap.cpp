#include "StdAfx.h"
#include "cObjMap.h"
#include "cObjLoader.h"
#include "cGroup.h"

cObjMap::cObjMap(void)
{
}


cObjMap::~cObjMap(void)
{
	for each(auto p in m_vecGroup)
	{
		SAFE_DELETE(p);
	}
}

void cObjMap::Load( char* szMap, char* szSurface, D3DXMATRIXA16* pmat )
{
	cObjLoader l;
	l.Load(szMap, m_vecGroup);

	std::vector<D3DXVECTOR3> vecV;

	FILE* fp = NULL;
	fopen_s(&fp, szSurface, "r");
	while(!feof(fp))
	{
		char szBuf[1024] = {'\0', };

		fgets(szBuf, 1024, fp);

		if(strlen(szBuf) == 0)
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
				if(pmat)
				{
					D3DXVec3TransformCoord(&p, &p, pmat);
				}
				m_vecSurface.push_back(p);
			}
		}
	}
	fclose(fp);
}

void cObjMap::Load(char* szMap, D3DXMATRIXA16* pmat)
{
	cObjLoader l;
	l.Load(szMap, m_vecGroup);
}


bool cObjMap::GetHeight( IN float x, OUT float& y, IN float z )
{
	D3DXVECTOR3 vRayPos(x, 1000, z);
	D3DXVECTOR3 vRayDir(0, -1, 0);

	for (size_t i = 0; i < m_vecSurface.size(); i += 3)
	{
		float u, v, d;
		if(D3DXIntersectTri(&m_vecSurface[i + 0],
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

void cObjMap::Render()
{
	//2016.11.13 - WIJY 
	//Scaling 삭제
	D3DXMATRIXA16 mat, matT, matS;
	//D3DXMatrixIdentity(&mat);
	//D3DXMatrixScaling(&matS, 0.1f, 0.1f, 0.1f);
	D3DXMatrixTranslation(&matT, 1.0, -1.15, 0);
	mat = matT;

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	for each(auto p in m_vecGroup)
	{
		p->Render();
	}
}
void cObjMap::Render(D3DXMATRIX * pMat)
{
	//2016.11.13 - WIJY 
	//Scaling 삭제
	/*D3DXMATRIXA16 mat, matT, matS;*/
	//D3DXMatrixIdentity(&mat);
	//D3DXMatrixScaling(&matS, 0.1f, 0.1f, 0.1f);
	//D3DXMatrixTranslation(&matT, value.x, value.y, value.z);
	//mat = matT;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, pMat);
	//g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	for each(auto p in m_vecGroup)
	{
		p->Render();
	}
}
