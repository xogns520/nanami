#pragma once
#include "cMtlTex.h"
#include "cObjLoader.h"

class cEffect
{
private :
	D3DXMATRIXA16				m_matWorld;

	char*						m_filePath;
	
	bool						m_bIsOn;
	float						m_fAnimationSpeed;
	float						m_fAlpha;
	
	bool						m_bIsSprite;			//스프라이트인지 mesh인지

	//sprite 변수
	LPD3DXSPRITE				m_pSprite;	
	LPDIRECT3DTEXTURE9			m_pSpriteTexture;
	RECT						m_rSpriteRect;

	//Mesh변수
	LPD3DXMESH					m_pMesh;
	std::vector<cMtlTex*>		m_vecMeshMtlTex;

	D3DXVECTOR3					m_centerPosition;

public :
	cEffect();

	~cEffect();

	void Destroy();

	void Setup(char* path, bool isSprite, float animationSpeed, float alpha);
	void Update();
	void Render();

	//Get/Set
	vector<cMtlTex*>*	GetVecMtlTexRef()	{ return &m_vecMeshMtlTex; }
	LPD3DXMESH*			GetMesh()			{ return &m_pMesh; }
	LPD3DXSPRITE*		GetSprite()			{ return &m_pSprite; }
	D3DXVECTOR3			GetPosition()		{ return m_centerPosition; }


	void		SetCenter(D3DXVECTOR3 pos)	{ m_centerPosition = pos; }
	void		SetSpriteSize(D3DXMATRIXA16 mat);
};

