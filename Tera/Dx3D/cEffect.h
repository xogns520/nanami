#pragma once
#include "cMtlTex.h"


class cEffect
{
private :
	char*						m_filePath;
	
	bool						m_bIsOn;
	float						m_fAnimationSpeed;
	float						m_fAlpha;
	
	bool						m_bIsSprite;			//��������Ʈ���� mesh����
	LPD3DXSPRITE				m_pSprite;	

	LPD3DXMESH					m_pMesh;
	std::vector<cMtlTex*>		m_vecMtlTex;

public :
	cEffect();

	~cEffect();

	void Destroy();

	void Setup(char* path, bool isSprite, float animationSpeed, float alpha);
	void Update();
	void Render();

	//Get/Set
	vector<cMtlTex*>*	GetVecMtlTexRef()	{ return &m_vecMtlTex; }
	LPD3DXMESH*			GetMesh()			{ return &m_pMesh; }
	LPD3DXSPRITE*		GetSprite()			{ return &m_pSprite; }
};

