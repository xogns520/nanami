#pragma once

struct ST_BONE;

class cTail
{
	friend class cSkinnedMeshManager;

private:
	//�ϳ��� ����
	ST_BONE*					m_pRootFrame;
	DWORD						m_dwWorkingPaletteSize;
	D3DXMATRIX*					m_pmWorkingPalette;
	LPD3DXEFFECT				m_pEffect;
	ST_SPHERE					m_stBoundingSphere;

	// ��ü���� ����
	LPD3DXANIMATIONCONTROLLER	m_pAnimController;
	D3DXVECTOR3					m_vPosition;

public:
	D3DXMATRIX					m_matNeckTM;
	D3DXMATRIX					m_matHairTM;
	D3DXMATRIX					m_matRootTM;
	D3DXMATRIX					m_matTailTM;

public:
	cTail(char* szFolder, char* szFilename);
	~cTail(void);

	void UpdateAndRender();
	void SetAnimationIndex(int nIndex);

	void SetRandomTrackPosition(); // �׽�Ʈ��
	void SetPosition(D3DXVECTOR3 v)
	{
		m_vPosition = v;
		m_stBoundingSphere.vCenter = v;
	}
	ST_SPHERE* GetBoundingSphere()
	{
		return &m_stBoundingSphere;
	}

private:
	cTail();
	void Load(char* szFolder, char* szFilename);
	LPD3DXEFFECT LoadEffect(char* szFilename);
	void Update(ST_BONE* pCurrent, D3DXMATRIXA16* pmatParent);
	void Render(ST_BONE* pBone = NULL);
	void SetupBoneMatrixPtrs(ST_BONE* pBone);
	void Destroy();
};

