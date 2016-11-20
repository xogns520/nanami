#pragma once

class iMap;
class cMapSkinnedMesh;

class cMap
{
private:
	//iMap*						m_pTerrain;

	cMapSkinnedMesh*				m_pTest;

	cMapSkinnedMesh*				m_pTerrain;

	cMapSkinnedMesh*				m_pPotion;

public:
	cMap();
	~cMap();

	void Setup();
	void Update();
	void Render();
};

