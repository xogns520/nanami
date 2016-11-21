#pragma once
#include "cMapAllocateHierarchy.h"

class cMapSkinnedMesh
{
private:
	MAP_ST_BONE*				m_pRoot;
	LPD3DXANIMATIONCONTROLLER	m_pAnimController;
	D3DXVECTOR3					m_vPosition;
	ST_SPHERE					m_stBoundingSphere;

public:
	cMapSkinnedMesh(void);
	virtual ~cMapSkinnedMesh(void);

	virtual void Load(char* szFolder, char* szFile);
	virtual void Update();
	virtual void Render();

	void SetPosition(D3DXVECTOR3 v)
	{
		m_vPosition = v;
		m_stBoundingSphere.vCenter += v;
	}
	D3DXVECTOR3* GetPosition()
	{
		return &m_vPosition;
	}

protected:
	virtual void Update(MAP_ST_BONE* pFrame, MAP_ST_BONE* pParent);
	virtual void Update2(MAP_ST_BONE* pCurrent, D3DXMATRIXA16* pmatParent);
	virtual void Render(MAP_ST_BONE* pFrame);
	virtual void SetupBoneMatrixPtrs(MAP_ST_BONE* pFrame);
	virtual void UpdateSkinnedMesh(MAP_ST_BONE* pFrame);
};

