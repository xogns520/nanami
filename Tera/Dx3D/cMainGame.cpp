#include "StdAfx.h"
#include "cMainGame.h"
#include "cCamera.h"
#include "cGrid.h"
#include "cCharController.h"
#include "cSkinnedMesh.h"
#include "cSkinnedMeshManager.h"
#include "cPlayer.h"
#include "cSkyBox.h"
#include "cObject.h"
#include "cObjLoader.h"
#include "cObjMap.h"
#include "cEffect.h"



cMainGame::cMainGame(void)
	: m_pCamera(NULL)
	, m_pGrid(NULL)
	, m_pCharController(NULL)
	, m_pMap(NULL)
	, m_pPlayer(NULL)
	, m_pPlayerDash(NULL)
	, m_pSkyBox(NULL)
	, m_pField(NULL)
	, m_pWall(NULL)
	, m_pGate1(NULL)
	, m_pGate2(NULL)
{
}

cMainGame::~cMainGame(void)
{
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_pCharController);
	SAFE_DELETE(m_pMap);
	SAFE_DELETE(m_pPlayer);
	SAFE_DELETE(m_pPlayerDash);
	SAFE_DELETE(m_pSkyBox);
	SAFE_DELETE(m_pField);
	SAFE_DELETE(m_pWall);
	SAFE_DELETE(m_pGate1);
	SAFE_DELETE(m_pGate2);

	for each (auto p in m_vecSkinnedMesh)
	{
		SAFE_DELETE(p);
	}

	g_pFontManager->Destroy();
	g_pTextureManager->Destroy();
	g_pSkinnedMeshManager->Destroy();
	g_pDeviceManager->Destroy();
	g_pObjectPool->Destroy();
}

void cMainGame::Setup()
{
	m_pCamera = new cCamera;
	m_pCamera->Setup();

	m_pGrid = new cGrid;
	m_pGrid->Setup(30);

	//m_effects = new cEffect;
	
	
	//m_mapEffect["fileBall"] = g_pSkinnedMeshManager->GetSkinnedMesh(m_folderNm, "EffectFireball.X");

	LPSTR sky[6] = { "skybox/Top.bmp", "skybox/Front.bmp", "skybox/Back.bmp", "skybox/Right.bmp", "skybox/Left.bmp", "skybox/Bottom.bmp" };

	//skybox
	m_pSkyBox = new cSkyBox;
	m_pSkyBox->Setup(sky);

	//map
	D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);
		
	D3DXMatrixTranslation(&mat, 0.0f, -500.0f, 0.0f);
	cObjMap* pMap = new cObjMap;
	pMap->Load("./Tera/Map/map.object", &mat);
	m_pField = pMap;
	//m_pField->
	
	
	D3DXMatrixTranslation(&mat, 0.0f, -50.0f, 0.0f);
	cObjMap* pMap2 = new cObjMap;
	pMap2->Load("./Tera/Wall.object", &mat);
	m_pWall = pMap2;

	D3DXMatrixTranslation(&mat, 50.0f, 0.0f, 150.0f);
	cObjMap* pMap3 = new cObjMap;
	pMap3->Load("./Tera/Map/Pie.object", &mat); 
	m_pGate1 = pMap3;

	D3DXMatrixTranslation(&mat, 50.0f, 0.0f, 150.0f);
	cObjMap* pMap4 = new cObjMap;
	pMap4->Load("./Tera/Map/PE_BD_Gate02_SM.object", &mat);
	m_pGate2 = pMap4;


	for (int x = -20; x <= 20; ++x)
	{
		if (x > -5 && x < 5) continue;
		for (int z = 10; z <= 30; ++z)
		{
			if (z > 17 && z < 23) continue;
			cSkinnedMesh* p = new cSkinnedMesh("Zealot/", "zealot.X");
			p->SetPosition(D3DXVECTOR3(x, 0, z));
			p->SetRandomTrackPosition();
			p->SetAnimationIndex(rand() % 5);
			m_vecSkinnedMesh.push_back(p);
		}
	}
	

	//m_effectTest = new cSkinnedMesh("./Tera/Effects/", "EffectFireball.X", "NOANIMATION");
	//m_effectTest = new cSkinnedMesh("./Zealot/", "zealot.X", "NOANIMATION");
	//m_effectTest->SetPosition(D3DXVECTOR3(0, 0, 0));
	
	//2016-11-20
	//skinnedMesh Render함수 분리 혹은 별도로 사용하도록 수정 필요!!!!!
	

	m_pCharController = new cCharController;

	m_pPlayer = new cPlayer;
	//m_pPlayer->Setup("./Tera/Character/", "Elin_Body_Wait.X", "Elin_Head_Wait.X", "Elin_Hair_Wait.X", NULL);
	m_pPlayer->Setup("./Tera/Character/", "Elin_Body_WD.X", "Elin_Face_WD.X", "Elin_Hair_WD.X", NULL);
	
	
	m_pPlayerDash = new cPlayer;
	m_pPlayerDash->Setup("./Tera/Character/", "Elin_Body_Dash.X", "Elin_Head_Dash.X", "Elin_Hair_Dash.X", NULL);

	SetLight();
}

void cMainGame::Update()
{
	g_pTimeManager->Update();
	
	if(m_pCharController)
		m_pCharController->Update(m_pMap);

	if(m_pCamera)
		m_pCamera->Update(m_pCharController->GetAngle(), m_pCharController->GetPosition());

	//int n = 0;
	if (m_pPlayer)
		//m_pPlayer->Update(m_pCharController->GetMoveKey());
		m_pPlayer->Update(2);

	// 	if(m_pSkinnedMesh)
// 	{
// 		D3DXMATRIXA16 mat;
// 		D3DXMatrixTranslation(&mat, 1, 0, 0);
// 		m_pSkinnedMesh->Update(&mat);
// 	}
	g_pAutoReleasePool->Drain();
}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(47, 121, 112),
		//D3DCOLOR_XRGB(0, 0, 255),
		1.0f, 0);

	g_pD3DDevice->BeginScene();

	// 그림을 그린다.

	D3DXMATRIXA16 mat;
	mat._41 = m_pCamera->GetEye().x;
	mat._42 = m_pCamera->GetEye().y;
	mat._43 = m_pCamera->GetEye().z;


	//if (m_pSkyBox)
	//	m_pSkyBox->Render(&mat);
	D3DXVECTOR3 tempPos;
	tempPos.x = 0.0f;
	tempPos.y = 0.0f;
	tempPos.z = 0.0f;


	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, -50.0f, -30.0f, 50.0f);
	//if (m_pField)
	//	m_pField->Render(&matT);
	

	//D3DXMATRIXA16 matT2;
	//D3DXMatrixTranslation(&matT2, 0.0f, 0.0f, 0.0f);
	//if (m_pWall)
	//	m_pWall->Render(&matT2);

	D3DXMatrixTranslation(&matT, 0.0f, 0.0f, 0.0f);

	if (m_pGate1)
		m_pGate1->Render(&matT);

	//if (m_pGate2)
	//	m_pGate2->Render(&matT);
	
	if (m_pGrid)
		m_pGrid->Render();

	for each (auto p in m_vecSkinnedMesh)
	{
		p->UpdateAndRender();
	}

	//if(!m_pCharController->GetMoveKey())

	

	//2016-11-20 
	//수정하다 말았음
	//if (m_effectTest)
	//	m_effectTest->UpdateAndRender();
	
	//if (m_pCharController->GetMoveKey())
	//	if (m_pPlayerDash)
	//		m_pPlayerDash->Render(&m_pCharController->GetWorldTM());



		
	g_pD3DDevice->EndScene();

	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	if(m_pCamera)
	{
		m_pCamera->WndProc(hWnd, message, wParam, lParam);
	}

	switch(message)
	{
	case WM_KEYDOWN:
		{
			//if (wParam == 'W')
			//{
			//	//static int n = 0;
			//	//m_pSkinnedMesh->SetAnimationIndex(++n);
			//	if (m_pPlayer)
			//		m_pPlayer->Update(2);
			//}
		}
		break;

	case WM_KEYUP:
	{
		//if (wParam == 'W')
		//{
		//	if (m_pPlayer)
		//		m_pPlayer->Update(1);
		//}
	}
		break;
	}
}

void cMainGame::SetLight()
{
	D3DLIGHT9 stLight;
	stLight.Ambient = stLight.Diffuse = stLight.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	stLight.Type = D3DLIGHT_DIRECTIONAL;
	D3DXVECTOR3 vDir(1, -1, 1);
	D3DXVec3Normalize(&vDir, &vDir);
	stLight.Direction = vDir;
	g_pD3DDevice->SetLight(0, &stLight);

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, false);
	g_pD3DDevice->LightEnable(0, false);
}

