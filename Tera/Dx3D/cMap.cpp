#include "stdafx.h"
#include "cMap.h"
#include "cMapSkinnedMesh.h"


cMap::cMap()
:m_pTest(NULL)

, m_pTerrain(NULL)
, m_pSurface_ter(NULL)

, m_pPotion(NULL)

, m_pTrees_bossZoneLeft(NULL)
, m_pStones_bossZoneLeft(NULL)

, m_pHouse2(NULL)
, m_pStone1_house2(NULL)
, m_pStone2_house2(NULL)
, m_pFlag1_house2(NULL)
, m_pFlag2_house2(NULL)
, m_pCart_house2(NULL)
, m_pCartburned_house2(NULL)
, m_pFence1_house2Back(NULL)
, m_pFence2_house2Back(NULL)
, m_pFence1_house2Front(NULL)
, m_pFence2_house2Front(NULL)
, m_pFence3_house2Front(NULL)
, m_pFence4_house2Front(NULL)

, m_pHouse1(NULL)
, m_pDoor_House1(NULL)

, m_pWoodFence0_house1(NULL)
, m_pWoodFence1_house1(NULL)
, m_pWoodFence2_house1(NULL)
, m_pWoodFence3_house1(NULL)
, m_pWoodFence4_house1(NULL)
, m_pWoodFence5_house1(NULL)
, m_pWoodFence6_house1(NULL)

, m_pStoneFence1_house1(NULL)
, m_pStoneFence2_house1(NULL)
, m_pStoneFence3_house1(NULL)
, m_pStoneFence4_house1(NULL)
, m_pStoneFence5_house1(NULL)
, m_pStoneFence6_house1(NULL)
, m_pStoneFence7_house1(NULL)
, m_pStoneFence8_house1(NULL)
, m_pStoneFence9_house1(NULL)
, m_pStoneFence10_house1(NULL)

, m_pTree0_house1(NULL)
, m_pTree1_house1(NULL)
, m_pTree2_house1(NULL)
, m_pTree3_house1(NULL)
, m_pTree4_house1(NULL)
, m_pTree5_house1(NULL)
, m_pTree6_house1(NULL)
, m_pTree7_house1(NULL)
, m_pTree8_house1(NULL)

, m_pStone_velicaLeft(NULL)
, m_pStone2_velicaLeft(NULL)
, m_pTree_velicaLeft(NULL)

, m_pStone_velicaRight(NULL)
, m_pStone2_velicaRight(NULL)

, m_pTree_velicaFront(NULL)

, m_pVelica(NULL)
{
}
cMap::~cMap()
{
	SAFE_DELETE(m_pTest);

	SAFE_DELETE(m_pTerrain);
	SAFE_DELETE(m_pSurface_ter);

	SAFE_DELETE(m_pPotion);

	SAFE_DELETE(m_pTrees_bossZoneLeft);
	SAFE_DELETE(m_pStones_bossZoneLeft);

	SAFE_DELETE(m_pHouse2);

	SAFE_DELETE(m_pStone1_house2);
	SAFE_DELETE(m_pStone2_house2);

	SAFE_DELETE(m_pFlag1_house2);
	SAFE_DELETE(m_pFlag2_house2);

	SAFE_DELETE(m_pCart_house2);
	SAFE_DELETE(m_pCartburned_house2);

	SAFE_DELETE(m_pFence1_house2Back);
	SAFE_DELETE(m_pFence2_house2Back);

	SAFE_DELETE(m_pFence1_house2Front);
	SAFE_DELETE(m_pFence2_house2Front);
	SAFE_DELETE(m_pFence3_house2Front);
	SAFE_DELETE(m_pFence4_house2Front);

	SAFE_DELETE(m_pHouse1);
	SAFE_DELETE(m_pDoor_House1);

	SAFE_DELETE(m_pWoodFence0_house1);
	SAFE_DELETE(m_pWoodFence1_house1);
	SAFE_DELETE(m_pWoodFence2_house1);
	SAFE_DELETE(m_pWoodFence3_house1);
	SAFE_DELETE(m_pWoodFence4_house1);
	SAFE_DELETE(m_pWoodFence5_house1);
	SAFE_DELETE(m_pWoodFence6_house1);

	SAFE_DELETE(m_pStoneFence1_house1);
	SAFE_DELETE(m_pStoneFence2_house1);
	SAFE_DELETE(m_pStoneFence3_house1);
	SAFE_DELETE(m_pStoneFence4_house1);
	SAFE_DELETE(m_pStoneFence5_house1);
	SAFE_DELETE(m_pStoneFence6_house1);
	SAFE_DELETE(m_pStoneFence7_house1);
	SAFE_DELETE(m_pStoneFence8_house1);
	SAFE_DELETE(m_pStoneFence9_house1);
	SAFE_DELETE(m_pStoneFence10_house1);

	SAFE_DELETE(m_pTree0_house1);
	SAFE_DELETE(m_pTree1_house1);
	SAFE_DELETE(m_pTree2_house1);
	SAFE_DELETE(m_pTree3_house1);
	SAFE_DELETE(m_pTree4_house1);
	SAFE_DELETE(m_pTree5_house1);
	SAFE_DELETE(m_pTree6_house1);
	SAFE_DELETE(m_pTree7_house1);
	SAFE_DELETE(m_pTree8_house1);

	SAFE_DELETE(m_pStone_velicaLeft);
	SAFE_DELETE(m_pStone2_velicaLeft);
	SAFE_DELETE(m_pTree_velicaLeft);

	SAFE_DELETE(m_pStone_velicaRight);
	SAFE_DELETE(m_pStone2_velicaRight);

	SAFE_DELETE(m_pTree_velicaFront);

	SAFE_DELETE(m_pVelica);
}

void cMap::Setup()
{

	//SetLight();

	//지형
	m_pTerrain = new cMapSkinnedMesh;
	m_pTerrain->Load("Tera/Map/EntireMap/moveMap", "moveMap.X"); //0.01 
	m_pTerrain->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_pSurface_ter = new cMapSkinnedMesh;
	m_pSurface_ter->Load("Tera/Map/EntireMap/moveMapSurface", "moveMapSurface.X"); //0.01 
	m_pSurface_ter->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));


	//아이템
	m_pPotion = new cMapSkinnedMesh;
	m_pPotion->Load("Tera/Item", "Potion.X");
	m_pPotion->SetPosition(D3DXVECTOR3(1.0f, 5.0f, 0.0f));


	//데코 (맵 위에 세울 오브젝트들)
	//보스존입구 왼쪽
	m_pTrees_bossZoneLeft = new cMapSkinnedMesh;
	m_pTrees_bossZoneLeft->Load("Tera/Map/EntireMap/ST_beside_bossZone", "Trees_besideBossZone.X");
	//"Tera/Map/EntireMap/ST_beside_bossZone", "Trees_besideBossZone.X"
	m_pTrees_bossZoneLeft->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f)); //셋포지션을 하지 않으면 안보임 

	m_pStones_bossZoneLeft = new cMapSkinnedMesh;
	m_pStones_bossZoneLeft->Load("Tera/Map/EntireMap/ST_beside_bossZone", "Stones_besideBossZone.X");
	m_pStones_bossZoneLeft->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));


	//보스존입구 오른쪽 집2지역 
	m_pHouse2 = new cMapSkinnedMesh;
	m_pHouse2->Load("Tera/Map/EntireMap/House2", "House2.X");
	//"Tera/Map/EntireMap/ST_beside_bossZone", "Trees_besideBossZone.X"
	m_pHouse2->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_pStone1_house2 = new cMapSkinnedMesh;
	m_pStone1_house2->Load("Tera/Map/EntireMap/House2", "Stone1_house2.X");
	m_pStone1_house2->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_pStone2_house2 = new cMapSkinnedMesh;
	m_pStone2_house2->Load("Tera/Map/EntireMap/House2", "Stone2_house2.X");
	m_pStone2_house2->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_pFlag1_house2 = new cMapSkinnedMesh;
	m_pFlag1_house2->Load("Tera/Map/EntireMap/House2", "Flag.X");
	m_pFlag1_house2->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_pFlag2_house2 = new cMapSkinnedMesh;
	m_pFlag2_house2->Load("Tera/Map/EntireMap/House2", "Flag2.X");
	m_pFlag2_house2->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_pCart_house2 = new cMapSkinnedMesh;
	m_pCart_house2->Load("Tera/Map/EntireMap/House2", "Cart.X");
	m_pCart_house2->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_pCartburned_house2 = new cMapSkinnedMesh;
	m_pCartburned_house2->Load("Tera/Map/EntireMap/House2", "Cart_burned.X");
	m_pCartburned_house2->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_pFence1_house2Back = new cMapSkinnedMesh;
	m_pFence1_house2Back->Load("Tera/Map/EntireMap/House2", "Fence1_house2Back.X");
	m_pFence1_house2Back->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_pFence2_house2Back = new cMapSkinnedMesh;
	m_pFence2_house2Back->Load("Tera/Map/EntireMap/House2", "Fence2_house2Back.X");
	m_pFence2_house2Back->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_pFence1_house2Front = new cMapSkinnedMesh;
	m_pFence1_house2Front->Load("Tera/Map/EntireMap/House2", "Fence1_house2Front.X");
	m_pFence1_house2Front->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_pFence2_house2Front = new cMapSkinnedMesh;
	m_pFence2_house2Front->Load("Tera/Map/EntireMap/House2", "Fence2_house2Front.X");
	m_pFence2_house2Front->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_pFence3_house2Front = new cMapSkinnedMesh;
	m_pFence3_house2Front->Load("Tera/Map/EntireMap/House2", "Fence3_house2Front.X");
	m_pFence3_house2Front->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_pFence4_house2Front = new cMapSkinnedMesh;
	m_pFence4_house2Front->Load("Tera/Map/EntireMap/House2", "Fence4_house2Front.X");
	m_pFence4_house2Front->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));


	//벨리카마을 밖 오른쪽 집1지역
	m_pHouse1 = new cMapSkinnedMesh;
	m_pHouse1->Load("Tera/Map/EntireMap/House1", "House1.X");
	m_pHouse1->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pDoor_House1 = new cMapSkinnedMesh;
	m_pDoor_House1->Load("Tera/Map/EntireMap/House1", "door_house.X");
	m_pDoor_House1->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_pWoodFence0_house1 = new cMapSkinnedMesh;
	m_pWoodFence0_house1->Load("Tera/Map/EntireMap/House1", "WoodFence0_house1.X");
	m_pWoodFence0_house1->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));		 
	m_pWoodFence1_house1 = new cMapSkinnedMesh;								
	m_pWoodFence1_house1->Load("Tera/Map/EntireMap/House1", "WoodFence1_house1.X");
	m_pWoodFence1_house1->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));		
	m_pWoodFence2_house1 = new cMapSkinnedMesh;								
	m_pWoodFence2_house1->Load("Tera/Map/EntireMap/House1", "WoodFence2_house1.X");
	m_pWoodFence2_house1->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));		
	m_pWoodFence3_house1 = new cMapSkinnedMesh;								
	m_pWoodFence3_house1->Load("Tera/Map/EntireMap/House1", "WoodFence3_house1.X");
	m_pWoodFence3_house1->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));		
	m_pWoodFence4_house1 = new cMapSkinnedMesh;								
	m_pWoodFence4_house1->Load("Tera/Map/EntireMap/House1", "WoodFence4_house1.X");
	m_pWoodFence4_house1->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));		
	m_pWoodFence5_house1 = new cMapSkinnedMesh;								 
	m_pWoodFence5_house1->Load("Tera/Map/EntireMap/House1", "WoodFence5_house1.X");
	m_pWoodFence5_house1->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));		 
	m_pWoodFence6_house1 = new cMapSkinnedMesh;								 
	m_pWoodFence6_house1->Load("Tera/Map/EntireMap/House1", "WoodFence6_house1.X");
	m_pWoodFence6_house1->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_pStoneFence1_house1 = new cMapSkinnedMesh;
	m_pStoneFence1_house1->Load("Tera/Map/EntireMap/House1", "StoneFence1_house1.X");
	m_pStoneFence1_house1->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pStoneFence2_house1 = new cMapSkinnedMesh;
	m_pStoneFence2_house1->Load("Tera/Map/EntireMap/House1", "StoneFence2_house1.X");
	m_pStoneFence2_house1->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pStoneFence3_house1 = new cMapSkinnedMesh;
	m_pStoneFence3_house1->Load("Tera/Map/EntireMap/House1", "StoneFence3_house1.X");
	m_pStoneFence3_house1->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pStoneFence4_house1 = new cMapSkinnedMesh;
	m_pStoneFence4_house1->Load("Tera/Map/EntireMap/House1", "StoneFence4_house1.X");
	m_pStoneFence4_house1->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pStoneFence5_house1 = new cMapSkinnedMesh;
	m_pStoneFence5_house1->Load("Tera/Map/EntireMap/House1", "StoneFence5_house1.X");
	m_pStoneFence5_house1->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pStoneFence6_house1 = new cMapSkinnedMesh;
	m_pStoneFence6_house1->Load("Tera/Map/EntireMap/House1", "StoneFence6_house1.X");
	m_pStoneFence6_house1->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pStoneFence7_house1 = new cMapSkinnedMesh;
	m_pStoneFence7_house1->Load("Tera/Map/EntireMap/House1", "StoneFence7_house1.X");
	m_pStoneFence7_house1->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pStoneFence8_house1 = new cMapSkinnedMesh;
	m_pStoneFence8_house1->Load("Tera/Map/EntireMap/House1", "StoneFence8_house1.X");
	m_pStoneFence8_house1->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pStoneFence9_house1 = new cMapSkinnedMesh;
	m_pStoneFence9_house1->Load("Tera/Map/EntireMap/House1", "StoneFence9_house1.X");
	m_pStoneFence9_house1->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_pTree0_house1 = new cMapSkinnedMesh;
	m_pTree0_house1->Load("Tera/Map/EntireMap/House1", "Tree0_house1.X");
	m_pTree0_house1->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pTree1_house1 = new cMapSkinnedMesh;
	m_pTree1_house1->Load("Tera/Map/EntireMap/House1", "Tree1_house1.X");
	m_pTree1_house1->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pTree2_house1 = new cMapSkinnedMesh;
	m_pTree2_house1->Load("Tera/Map/EntireMap/House1", "Tree2_house1.X");
	m_pTree2_house1->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pTree3_house1 = new cMapSkinnedMesh;
	m_pTree3_house1->Load("Tera/Map/EntireMap/House1", "Tree3_house1.X");
	m_pTree3_house1->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pTree4_house1 = new cMapSkinnedMesh;
	m_pTree4_house1->Load("Tera/Map/EntireMap/House1", "Tree4_house1.X");
	m_pTree4_house1->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pTree5_house1 = new cMapSkinnedMesh;
	m_pTree5_house1->Load("Tera/Map/EntireMap/House1", "Tree5_house1.X");
	m_pTree5_house1->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pTree6_house1 = new cMapSkinnedMesh;
	m_pTree6_house1->Load("Tera/Map/EntireMap/House1", "Tree6_house1.X");
	m_pTree6_house1->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));


	//벨리카마을 밖 왼쪽 지역
	m_pStone_velicaLeft = new cMapSkinnedMesh;
	m_pStone_velicaLeft->Load("Tera/Map/EntireMap/ST_velicaLeft", "Stone_velicaLeft.X");
	m_pStone_velicaLeft->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pStone2_velicaLeft = new cMapSkinnedMesh;
	m_pStone2_velicaLeft->Load("Tera/Map/EntireMap/ST_velicaLeft", "Stone2_velicaLeft.X");
	m_pStone2_velicaLeft->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pTree_velicaLeft = new cMapSkinnedMesh;
	m_pTree_velicaLeft->Load("Tera/Map/EntireMap/ST_velicaLeft", "Tree_velicaLeft.X");
	//Tera/Map/EntireMap/ST_velicaLeft", "Tree_velicaLeft.X
	m_pTree_velicaLeft->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//벨리카마을 밖 오른쪽 지역
	m_pStone_velicaRight = new cMapSkinnedMesh;
	m_pStone_velicaRight->Load("Tera/Map/EntireMap/ST_velicaRight", "Stone_velicaRight.X");
	m_pStone_velicaRight->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pStone2_velicaRight = new cMapSkinnedMesh;
	m_pStone2_velicaRight->Load("Tera/Map/EntireMap/ST_velicaRight", "Stone2_velicaRight.X");
	m_pStone2_velicaRight->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//벨리카마을 밖 앞 지역
	m_pTree_velicaFront = new cMapSkinnedMesh;
	m_pTree_velicaFront->Load("Tera/Map/EntireMap/ST_velicaFront", "Tree_velicaFront.X");
	m_pTree_velicaFront->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//벨리카마을
	m_pVelica = new cMapSkinnedMesh;
	m_pVelica->Load("Tera/Map/EntireMap/Velica", "Velica.X");
	m_pVelica->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

}

void cMap::Update()
{
	//업데이트에서 포지션변경

	//지형
	if (m_pTerrain)
		m_pTerrain->Update();

	//if (m_pSurface_ter)
	//	m_pSurface_ter->Update();


	////아이템
	//if (m_pPotion)
	//	m_pPotion->Update();


	//데코 (맵 위에 세울 오브젝트들)
	//보스존입구 왼쪽
	if (m_pTrees_bossZoneLeft)
		m_pTrees_bossZoneLeft->Update();
	if (m_pStones_bossZoneLeft)
		m_pStones_bossZoneLeft->Update();

	//보스존입구 오른쪽 집2지역
	if (m_pHouse2)
		m_pHouse2->Update();

	if (m_pStone1_house2)
		m_pStone1_house2->Update();
	if (m_pStone2_house2)
		m_pStone2_house2->Update();

	if (m_pFlag1_house2)
		m_pFlag1_house2->Update();
	if (m_pFlag2_house2)
		m_pFlag2_house2->Update();

	if (m_pCart_house2)
		m_pCart_house2->Update();
	if (m_pCartburned_house2)
		m_pCartburned_house2->Update();

	if (m_pFence1_house2Back)
		m_pFence1_house2Back->Update();
	if (m_pFence2_house2Back)
		m_pFence2_house2Back->Update();

	if (m_pFence1_house2Front)
		m_pFence1_house2Front->Update();
	if (m_pFence2_house2Front)
		m_pFence2_house2Front->Update();
	if (m_pFence3_house2Front)
		m_pFence3_house2Front->Update();
	if (m_pFence4_house2Front)
		m_pFence4_house2Front->Update();


	//벨리카마을 밖 오른쪽 집1지역
	if (m_pHouse1)
		m_pHouse1->Update();
	if (m_pDoor_House1)
		m_pDoor_House1->Update();

	if (m_pWoodFence0_house1)
		m_pWoodFence0_house1->Update();
	if (m_pWoodFence1_house1)
		m_pWoodFence1_house1->Update();
	if (m_pWoodFence2_house1)
		m_pWoodFence2_house1->Update();
	if (m_pWoodFence3_house1)
		m_pWoodFence3_house1->Update();
	if (m_pWoodFence4_house1)
		m_pWoodFence4_house1->Update();
	if (m_pWoodFence5_house1)
		m_pWoodFence5_house1->Update();
	if (m_pWoodFence6_house1)
		m_pWoodFence6_house1->Update();

	if (m_pStoneFence1_house1)
		m_pStoneFence1_house1->Update();
	if (m_pStoneFence2_house1)
		m_pStoneFence2_house1->Update();
	if (m_pStoneFence3_house1)
		m_pStoneFence3_house1->Update();
	if (m_pStoneFence4_house1)
		m_pStoneFence4_house1->Update();
	if (m_pStoneFence5_house1)
		m_pStoneFence5_house1->Update();
	if (m_pStoneFence6_house1)
		m_pStoneFence6_house1->Update();
	if (m_pStoneFence7_house1)
		m_pStoneFence7_house1->Update();
	if (m_pStoneFence8_house1)
		m_pStoneFence8_house1->Update();
	if (m_pStoneFence9_house1)
		m_pStoneFence9_house1->Update();


	if (m_pTree0_house1)
		m_pTree0_house1->Update();
	if (m_pTree1_house1)
		m_pTree1_house1->Update();
	if (m_pTree2_house1)
		m_pTree2_house1->Update();
	if (m_pTree3_house1)
		m_pTree3_house1->Update();
	if (m_pTree4_house1)
		m_pTree4_house1->Update();
	if (m_pTree5_house1)
		m_pTree5_house1->Update();
	if (m_pTree6_house1)
		m_pTree6_house1->Update();


	//벨리카마을 밖 왼쪽 지역
	if (m_pStone_velicaLeft)
		m_pStone_velicaLeft->Update();
	if (m_pStone2_velicaLeft)
		m_pStone2_velicaLeft->Update();
	if (m_pTree_velicaLeft)
		m_pTree_velicaLeft->Update();

	//벨리카마을 밖 오른쪽 지역
	if (m_pStone_velicaRight)
		m_pStone_velicaRight->Update();
	if (m_pStone2_velicaRight)
		m_pStone2_velicaRight->Update();

	//벨리카마을 밖 앞 지역
	if (m_pTree_velicaFront)
		m_pTree_velicaFront->Update();

	//벨리카마을
	if (m_pVelica)
		m_pVelica->Update();

}

void cMap::Render()
{

	//지형
	if (m_pTerrain)
		m_pTerrain->Render();

	//if (m_pSurface_ter)
	//	m_pSurface_ter->Render();


	////아이템
	//if (m_pPotion) 
	//	m_pPotion->Render();


	//데코 (맵 위에 세울 오브젝트들)
	//보스존입구 왼쪽
	if (m_pTrees_bossZoneLeft)
		m_pTrees_bossZoneLeft->Render();
	if (m_pStones_bossZoneLeft)
		m_pStones_bossZoneLeft->Render();


	//보스존입구 오른쪽 집2지역
	if (m_pHouse2)
		m_pHouse2->Render();
	if (m_pStone1_house2)
		m_pStone1_house2->Render();
	if (m_pStone2_house2)
		m_pStone2_house2->Render();
	if (m_pFlag1_house2)
		m_pFlag1_house2->Render();
	if (m_pFlag2_house2)
		m_pFlag2_house2->Render();


	if (m_pCart_house2)
		m_pCart_house2->Render();
	if (m_pCartburned_house2)
		m_pCartburned_house2->Render();

	if (m_pFence1_house2Back)
		m_pFence1_house2Back->Render();
	if (m_pFence2_house2Back)
		m_pFence2_house2Back->Render();

	if (m_pFence1_house2Front)
		m_pFence1_house2Front->Render();
	if (m_pFence2_house2Front)
		m_pFence2_house2Front->Render();
	if (m_pFence3_house2Front)
		m_pFence3_house2Front->Render();
	if (m_pFence4_house2Front)
		m_pFence4_house2Front->Render();


	////벨리카마을 밖 오른쪽 집1지역
	if (m_pHouse1)
		m_pHouse1->Render();
	if (m_pDoor_House1)
		m_pDoor_House1->Render();

	if (m_pWoodFence0_house1)
		m_pWoodFence0_house1->Render();
	if (m_pWoodFence1_house1)
		m_pWoodFence1_house1->Render();
	if (m_pWoodFence2_house1)
		m_pWoodFence2_house1->Render();
	if (m_pWoodFence3_house1)
		m_pWoodFence3_house1->Render();
	if (m_pWoodFence4_house1)
		m_pWoodFence4_house1->Render();
	if (m_pWoodFence5_house1)
		m_pWoodFence5_house1->Render();
	if (m_pWoodFence6_house1)
		m_pWoodFence6_house1->Render();

	if (m_pStoneFence1_house1)
		m_pStoneFence1_house1->Render();
	if (m_pStoneFence2_house1)
		m_pStoneFence2_house1->Render();
	if (m_pStoneFence3_house1)
		m_pStoneFence3_house1->Render();
	if (m_pStoneFence4_house1)
		m_pStoneFence4_house1->Render();
	if (m_pStoneFence5_house1)
		m_pStoneFence5_house1->Render();
	if (m_pStoneFence6_house1)
		m_pStoneFence6_house1->Render();
	if (m_pStoneFence7_house1)
		m_pStoneFence7_house1->Render();
	if (m_pStoneFence8_house1)
		m_pStoneFence8_house1->Render();
	if (m_pStoneFence9_house1)
		m_pStoneFence9_house1->Render();


	if (m_pTree0_house1)
		m_pTree0_house1->Render();
	if (m_pTree1_house1)
		m_pTree1_house1->Render();
	if (m_pTree2_house1)
		m_pTree2_house1->Render();
	if (m_pTree3_house1)
		m_pTree3_house1->Render();
	if (m_pTree4_house1)
		m_pTree4_house1->Render();
	if (m_pTree5_house1)
		m_pTree5_house1->Render();
	if (m_pTree6_house1)
		m_pTree6_house1->Render();


	//벨리카마을 밖 왼쪽 지역
	if (m_pStone_velicaLeft)
		m_pStone_velicaLeft->Render();
	if (m_pStone2_velicaLeft)
		m_pStone2_velicaLeft->Render();
	if (m_pTree_velicaLeft)
		m_pTree_velicaLeft->Render();

	//벨리카마을 밖 오른쪽 지역
	if (m_pStone_velicaRight)
		m_pStone_velicaRight->Render();
	if (m_pStone2_velicaRight)
		m_pStone2_velicaRight->Render();

	//벨리카마을 밖 앞 지역
	if (m_pTree_velicaFront)
		m_pTree_velicaFront->Render();

	//벨리카마을
	if (m_pVelica)
		m_pVelica->Render();
}

void cMap::SetLight()
{
	D3DLIGHT9 stLight;
	stLight.Ambient = stLight.Diffuse = stLight.Specular = D3DXCOLOR(0.95f, 0.95f, 0.95f, 1.0f);
	stLight.Type = D3DLIGHT_DIRECTIONAL;
	D3DXVECTOR3 vDir(1, -1, 1);
	D3DXVec3Normalize(&vDir, &vDir);
	stLight.Direction = vDir;
	g_pD3DDevice->SetLight(0, &stLight);

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	g_pD3DDevice->LightEnable(0, true);
}
