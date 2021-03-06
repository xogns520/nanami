#pragma once

class cSkinnedMesh;

class cOBB
{
private:
	D3DXVECTOR3 m_vOrgCenterPos;
	D3DXVECTOR3 m_vOrgAxisDir[3];

	D3DXVECTOR3 m_vCenterPos;		// 상자 중앙의 좌표
	D3DXVECTOR3 m_vAxisDir[3];		// 상자에 평행한 세 축의 단위벡터
	float		m_fAxisLen[3];		// 상자의 평행한 세 축의 길이 fAxisLen[n]은 vAxisDir[n]에 각각 대응한다.
	float		m_fAxisHalfLen[3];

	D3DXMATRIXA16 m_matWorldTM;
public:
	cOBB(void);
	~cOBB(void);

	void Setup(cSkinnedMesh* pSkinnedMesh);
	void Update(D3DXMATRIXA16* pmatWorld);
	void DebugRender(D3DCOLOR c);

	static bool IsCollision(cOBB* pOBB1, cOBB* pOBB2);
};

