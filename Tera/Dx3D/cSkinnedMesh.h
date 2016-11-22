#pragma once

struct ST_BONE;

class cSkinnedMesh
{
	friend class cSkinnedMeshManager;

private:
	//하나만 생성
	ST_BONE*					m_pRootFrame;			
	DWORD						m_dwWorkingPaletteSize;
	D3DXMATRIX*					m_pmWorkingPalette;
	LPD3DXEFFECT				m_pEffect;
	ST_SPHERE					m_stBoundingSphere;

	// 객체마다 생성
	LPD3DXANIMATIONCONTROLLER	m_pAnimController;
	D3DXVECTOR3					m_vPosition;
	ST_BOX						m_stBoundingBox;

public:
	cSkinnedMesh(char* szFolder, char* szFilename);
	cSkinnedMesh(char* szFolder, char* szFilename, char* NOANIMATION);		//temp

	~cSkinnedMesh(void);
	
	void UpdateAndRender(D3DXMATRIXA16* pmat = NULL);
	void SetAnimationIndex(int nIndex);

	void SetRandomTrackPosition(); // 테스트용
	void SetPosition(D3DXVECTOR3 v)
	{
		m_vPosition = v;
		m_stBoundingSphere.vCenter += v;
	}
	D3DXVECTOR3* GetPosition()
	{
		return &m_vPosition;
	}
	ST_SPHERE* GetBoundingSphere()
	{
		return &m_stBoundingSphere;
	}
	ST_BOX* GetBoundingBox()
	{
		return &m_stBoundingBox;
	}
private:
	cSkinnedMesh();
	void Load(char* szFolder, char* szFilename);
	LPD3DXEFFECT LoadEffect(char* szFilename);
	void Update(ST_BONE* pCurrent, D3DXMATRIXA16* pmatParent);
	void Render(ST_BONE* pBone = NULL);
	void SetupBoneMatrixPtrs(ST_BONE* pBone);
	void Destroy();
};

