#pragma once

class iMap;
class cMapSkinnedMesh;

class cMap
{
private:
	//iMap*						m_pTerrain;

	cMapSkinnedMesh*				m_pTest;

	//����
	cMapSkinnedMesh*				m_pTerrain;
	cMapSkinnedMesh*				m_pSurface_ter;

	//������
	cMapSkinnedMesh*				m_pPotion;

	//����
	cMapSkinnedMesh*				m_pPie;

	cMapSkinnedMesh*				m_pTrees_bossZoneLeft;
	cMapSkinnedMesh*				m_pStones_bossZoneLeft;



public:
	cMap();
	~cMap();

	void Setup();
	void Update();
	void Render();

	cMapSkinnedMesh* getTerrain(){ return m_pTerrain; }
	cMapSkinnedMesh* getSurface(){ return m_pSurface_ter; }
	cMapSkinnedMesh* getPotion(){ return m_pPotion; }
};

