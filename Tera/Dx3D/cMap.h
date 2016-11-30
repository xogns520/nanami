#pragma once

class iMap;
class cMapSkinnedMesh;

class cMap
{
private:
	cMapSkinnedMesh*				m_pTest;

	//����
	cMapSkinnedMesh*				m_pTerrain;//�� ��¦ ��߳��°� ����
	cMapSkinnedMesh*				m_pSurface_ter;

	//������
	cMapSkinnedMesh*				m_pPotion;

	//���� (�� ���� ���� ������Ʈ��)
	//�������Ա� ����
	cMapSkinnedMesh*				m_pTrees_bossZoneLeft;
	cMapSkinnedMesh*				m_pStones_bossZoneLeft;

	//�������Ա� ������ ��2����
	cMapSkinnedMesh*				m_pHouse2;

	cMapSkinnedMesh*				m_pStone1_house2;
	cMapSkinnedMesh*				m_pStone2_house2;

	cMapSkinnedMesh*				m_pFlag1_house2;
	cMapSkinnedMesh*				m_pFlag2_house2;

	cMapSkinnedMesh*				m_pCart_house2;
	cMapSkinnedMesh*				m_pCartburned_house2;

	cMapSkinnedMesh*				m_pFence1_house2Back;
	cMapSkinnedMesh*				m_pFence2_house2Back;

	cMapSkinnedMesh*				m_pFence1_house2Front;
	cMapSkinnedMesh*				m_pFence2_house2Front;
	cMapSkinnedMesh*				m_pFence3_house2Front;
	cMapSkinnedMesh*				m_pFence4_house2Front;

	//����ī���� �� ������ ��1����
	cMapSkinnedMesh*				m_pHouse1;
	cMapSkinnedMesh*				m_pDoor_House1;

	cMapSkinnedMesh*				m_pWoodFence0_house1;
	cMapSkinnedMesh*				m_pWoodFence1_house1;
	cMapSkinnedMesh*				m_pWoodFence2_house1;
	cMapSkinnedMesh*				m_pWoodFence3_house1;
	cMapSkinnedMesh*				m_pWoodFence4_house1;
	cMapSkinnedMesh*				m_pWoodFence5_house1;
	cMapSkinnedMesh*				m_pWoodFence6_house1;

	cMapSkinnedMesh*				m_pStoneFence1_house1; 
	cMapSkinnedMesh*				m_pStoneFence2_house1;
	cMapSkinnedMesh*				m_pStoneFence3_house1;
	cMapSkinnedMesh*				m_pStoneFence4_house1;
	cMapSkinnedMesh*				m_pStoneFence5_house1;
	cMapSkinnedMesh*				m_pStoneFence6_house1;
	cMapSkinnedMesh*				m_pStoneFence7_house1;
	cMapSkinnedMesh*				m_pStoneFence8_house1;
	cMapSkinnedMesh*				m_pStoneFence9_house1;
	cMapSkinnedMesh*				m_pStoneFence10_house1;

	cMapSkinnedMesh*				m_pTree0_house1;
	cMapSkinnedMesh*				m_pTree1_house1;
	cMapSkinnedMesh*				m_pTree2_house1;
	cMapSkinnedMesh*				m_pTree3_house1;
	cMapSkinnedMesh*				m_pTree4_house1;
	cMapSkinnedMesh*				m_pTree5_house1;
	cMapSkinnedMesh*				m_pTree6_house1;
	cMapSkinnedMesh*				m_pTree7_house1;
	cMapSkinnedMesh*				m_pTree8_house1;
	
	//����ī���� �� ���� ����
	cMapSkinnedMesh*				m_pStone_velicaLeft;  
	cMapSkinnedMesh*				m_pStone2_velicaLeft;
	cMapSkinnedMesh*				m_pTree_velicaLeft;

	//����ī���� �� ������ ����
	cMapSkinnedMesh*				m_pStone_velicaRight; //�� �ȶ� 
	cMapSkinnedMesh*				m_pStone2_velicaRight;

	//����ī���� �� �� ����
	cMapSkinnedMesh*				m_pTree_velicaFront;

	//����ī����
	cMapSkinnedMesh*				m_pVelica; //�� �ȶ�



public:
	cMap();
	~cMap();

	void Setup();
	void Update();
	void Render();

	void SetLight();

	cMapSkinnedMesh* getTerrain(){ return m_pTerrain; }
	cMapSkinnedMesh* getSurface(){ return m_pSurface_ter; }
	cMapSkinnedMesh* getPotion(){ return m_pPotion; }
};

