#pragma once
class cSkyBox
{
private:
	std::vector<ST_PT_VERTEX>	m_vecVertex;
	D3DXMATRIXA16				m_matWorld;
	LPDIRECT3DTEXTURE9			m_pTexture;
	D3DXMATRIXA16				m_matScale;
	LPDIRECT3DVERTEXBUFFER9		m_pVB;
	LPDIRECT3DTEXTURE9			m_pTex[6];
public:
	cSkyBox();
	~cSkyBox();

	void Setup(LPSTR lpTexFilename[6]);
	void Update();
	void Render(D3DXMATRIXA16* mat);
};

