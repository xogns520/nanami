#include "stdafx.h"
#include "cMap.h"
#include "cMapSkinnedMesh.h"


cMap::cMap()
:m_pTest(NULL)
, m_pTerrain(NULL)
, m_pPotion(NULL)
{
}
cMap::~cMap()
{
	SAFE_DELETE(m_pTest);
	SAFE_DELETE(m_pTerrain);
	SAFE_DELETE(m_pPotion);
}

void cMap::Setup()
{
	//TEST
	m_pTest = new cMapSkinnedMesh;
	m_pTest->Load("Zealot", "zealot.X");
	m_pTest->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//ÁöÇü
	m_pTerrain = new cMapSkinnedMesh;
	m_pTerrain->Load("Tera/Map", "Map.X");
	m_pTerrain->SetPosition(D3DXVECTOR3(50.0f, -70.0f, -50.0f));

	//Item
	m_pPotion = new cMapSkinnedMesh;
	m_pPotion->Load("Tera/Item", "Potion.X");
	m_pPotion->SetPosition(D3DXVECTOR3(-1.0f, 0.0f, 0.0f));
}

void cMap::Update()
{
	if (m_pTest)
		m_pTest->Update();

	if (m_pTerrain)
		m_pTerrain->Update();

	if (m_pPotion)
		m_pPotion->Update();
}

void cMap::Render()
{

	if (m_pTest)
		m_pTest->Render();

	if (m_pTerrain)
		m_pTerrain->Render();

	if (m_pPotion)
		m_pPotion->Render();
}
