#include "stdafx.h"
#include "cMap.h"
#include "cMapSkinnedMesh.h"


cMap::cMap()
:m_pTest(NULL)
, m_pTerrain(NULL)
, m_pSurface_ter(NULL)
, m_pPotion(NULL)
, m_pPie(NULL)
, m_pTrees_bossZoneLeft(NULL)
, m_pStones_bossZoneLeft(NULL)
, m_bSurFace(false)
{
}
cMap::~cMap()
{
	SAFE_DELETE(m_pTest);
	SAFE_DELETE(m_pTerrain);
	SAFE_DELETE(m_pSurface_ter);
	SAFE_DELETE(m_pPotion);
	SAFE_DELETE(m_pPie);
	SAFE_DELETE(m_pTrees_bossZoneLeft);
	SAFE_DELETE(m_pStones_bossZoneLeft);
}

void cMap::Setup()
{

	//지형
	m_pTerrain = new cMapSkinnedMesh;
	m_pTerrain->Load("Tera/Map/EntireMap/moveMap", "moveMap.X"); //0.01 
	//"Tera/Map/EntireMap/moveMap", "moveMap.X"
	m_pSurface_ter = new cMapSkinnedMesh;
	m_pSurface_ter->Load("Tera/Map/EntireMap/moveMapSurface", "moveMapSurface.X"); //0.01 


	//m_pTerrain->SetPosition(D3DXVECTOR3(50.0f, -30.0f, -50.0f));
	//0.0005
	m_pTerrain->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pSurface_ter->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//TEST
	m_pTest = new cMapSkinnedMesh;
	m_pTest->Load("Zealot", "zealot.X");
	m_pTest->SetPosition(D3DXVECTOR3(-10.0f, 0.0f, 10.0f));

	//Item
	m_pPotion = new cMapSkinnedMesh;
	//m_pPotion->Load("Tera/Map/EntireMap/ST_beside_bossZone", "Trees_besideBossZone.X");
	m_pPotion->Load("Tera/Item", "Potion.X");
	m_pPotion->SetPosition(D3DXVECTOR3(1.0f, 5.0f, 0.0f));

	m_pPie = new cMapSkinnedMesh;
	m_pPie->Load("Tera/MapDeco", "Pie.X");
	m_pPie->SetPosition(D3DXVECTOR3(-2.0f, 0.0f, 0.0f));

	//Deco
	m_pTrees_bossZoneLeft = new cMapSkinnedMesh;
	m_pTrees_bossZoneLeft->Load("Tera/Map/EntireMap/ST_beside_bossZone", "Trees_besideBossZone.X");
	m_pTrees_bossZoneLeft->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	m_pStones_bossZoneLeft = new cMapSkinnedMesh;
	m_pStones_bossZoneLeft->Load("Tera/Map/EntireMap/ST_beside_bossZone", "Stones_besideBossZone.X");
	m_pStones_bossZoneLeft->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}

void cMap::Update()
{
	int a = 0;
	//업데이트에서 포지션변경
	//if (m_pTerrain)
	//	m_pTerrain->Update();

	//if (m_pSurface_ter)
	//	m_pSurface_ter->Update();

	//if (m_pTest)
	//	m_pTest->Update();

	//if (m_pPotion)
	//	m_pPotion->Update();

	//if (m_pTrees_bossZoneLeft)
	//	m_pTrees_bossZoneLeft->Update();

	//if (m_pStones_bossZoneLeft)
	//	m_pStones_bossZoneLeft->Update();

	//if (m_pPie)
	//	m_pPie->Update();

	if (g_pKeyManager->isOnceKeyDown(VK_SPACE))
	{
		m_bSurFace = !m_bSurFace;
	}
}

void cMap::Render()
{
	if (m_pTerrain)
		if(!m_bSurFace)
		m_pTerrain->Render();

	if (m_pSurface_ter)
		if (m_bSurFace)
		m_pSurface_ter->Render();

	//float tempy = 0;
	//if (m_pTest)
	//	if(m_pTerrain->GetHeight(m_pTest->GetPosition()->x, tempy, m_pTest->GetPosition()->z));
	//{
	//	m_pTest->SetPosition(D3DXVECTOR3(m_pTest->GetPosition()->x, tempy, m_pTest->GetPosition()->z));
	//	//float y = tempy;
	//	m_pTest->Render();
	//}

	//if (m_pPotion) 
	//	m_pPotion->Render();

	////if (m_pPie)
	////	m_pPie->Render();

	//if (m_pTrees_bossZoneLeft)
	//	m_pTrees_bossZoneLeft->Render();

	//if (m_pStones_bossZoneLeft)
	//	m_pStones_bossZoneLeft->Render();


}
