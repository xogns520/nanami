#pragma once

class iMap;
class cMapSkinnedMesh;

class cCharController
{
private:
	D3DXVECTOR3					m_vPosition;
	D3DXVECTOR3					m_vDirection;
	float						m_fAngle;
	float						m_fSpeed;
	SYNTHESIZE_PASS_BY_REF(D3DXMATRIXA16, m_matWorld, WorldTM);
	SYNTHESIZE(int, m_nMoveKey, MoveKey);

public:
	cCharController(void);
	~cCharController(void);

	void Update(iMap* pMap = NULL);
	void Update(cMapSkinnedMesh* pMap = NULL);
	
	void SetPosition(D3DXVECTOR3* Pos)
	{
		m_vPosition = *Pos;
	}

	D3DXVECTOR3* GetPosition()
	{
		return &m_vPosition;
	}
	float GetAngle()
	{
		return m_fAngle;
	}
};

