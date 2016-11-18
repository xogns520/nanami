#pragma once
#include<string.h> 

#define RESOURCE_FOLDER "./Resources/"

class cMtlTex;
class cTerrain
{
public:
	LPDIRECT3DVERTEXBUFFER9		m_pVB;
	LPDIRECT3DINDEXBUFFER9		m_pIB;
	vector<D3DXVECTOR3>			m_vecV;
	vector<DWORD>				m_vecI;
	vector<ST_PNT_VERTEX>		m_vecVertex;
	vector<float>				m_vecHeight;
	vector<D3DXVECTOR3>			m_vecNormal;
	LPD3DXMESH					m_pMesh;
	cMtlTex*					m_pMtlTex;
	float						m_fBrightness;
	D3DXVECTOR3					m_vStart;
	D3DXVECTOR3					m_vEnd;
	D3DXVECTOR3					m_vCurrent;
	float						m_ft;
	float						m_fHeightRadio;	//���� ����
	vector<vector<D3DXVECTOR3>> m_vecvecVertex;	//���ؽ� 2������ ����

public:
	cTerrain();
	~cTerrain();
	void Setup();
	void Update();
	void Render();
	void BuildMesh(vector<ST_PNT_VERTEX>& vecVertex);
	float GetHeight(const D3DXVECTOR3& vPos);
	void cTerrain::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

