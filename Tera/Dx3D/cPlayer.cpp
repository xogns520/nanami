#include "stdafx.h"
#include "cPlayer.h"
#include "cBody.h"
#include "cFace.h"
#include "cHair.h"
#include "cTail.h"
#include "cWeapon.h"
#include "cWeaponTest.h"

cPlayer::cPlayer()
	: m_pBody(NULL)
	, m_pFace(NULL)
	, m_pHair(NULL)
	, m_pTail(NULL)
	, m_pRWeapon(NULL)
	, m_pLWeapon(NULL)
	, m_pT(NULL)
{
}


cPlayer::~cPlayer()
{
	SAFE_DELETE(m_pBody);
	SAFE_DELETE(m_pFace);
	SAFE_DELETE(m_pHair);
	SAFE_DELETE(m_pTail);
	SAFE_DELETE(m_pRWeapon);
	SAFE_DELETE(m_pLWeapon);
	SAFE_DELETE(m_pT);
}

void cPlayer::Setup(char * Directory, char * PathBody, char * PathFace, char * PathHair, char* PathTail)
{
	m_pBody = new cBody(Directory, PathBody);
	m_pFace = new cFace(Directory, PathFace);
	//m_pFace->m_matNeckTM = m_pBody->m_matNeckTM;
	//
	m_pHair = new cHair(Directory, PathHair);
	m_pTail = new cTail(Directory, PathTail);

	D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);

	//mat = m_pBody->m_matRWeaponTM;
	//mat = m_pBody->m_matNeckTM;

	//cWeapon* pW = new cWeapon;
	//pW->Load("./Tera/Character/Weapon_R.obj", &mat);
	//m_pMap = pW;

	//D3DXMATRIXA16 matT, matYR, matXR;
	//D3DXMatrixRotationY(&matYR, -1.75f);
	//D3DXMatrixRotationX(&matXR, 0.25f);
	//D3DXMatrixTranslation(&matT, -0.01f, 0.0f, 0.03f);
	//
	//mat = matXR * matT;

	m_pRWeapon = new cWeapon;
	m_pRWeapon->Load("./Tera/Character/Weapon_R.object", &mat);

	//D3DXMatrixRotationY(&matYR, -1.75f);
	//D3DXMatrixRotationX(&matXR, 3.25f);
	//D3DXMatrixRotationZ(&matXR, -2.75f);
	//D3DXMatrixTranslation(&matT, 0.01f, 0.0f, -0.0075f);
	//mat = matYR * matXR * matT;

	m_pLWeapon = new cWeapon;
	m_pLWeapon->Load("./Tera/Character/Weapon_L.object", &mat);

	//m_pT = new cWeaponTest(Directory, "Weapon_R.X");

	//m_pHair->m_matHairTM = m_pBody->m_matHairTM;
	//m_pHair->Load(Directory, PathHair);

	//cObjMap* pMap2 = new cObjMap;
	//pMap2->Load("./Tera/Wall.obj", &mat);
	//m_pWall = pMap2;
}

void cPlayer::Update(int AniIndex)
{
	m_pBody->SetAnimationIndex(AniIndex);
	m_pFace->SetAnimationIndex(AniIndex);
	m_pHair->SetAnimationIndex(AniIndex);
	m_pTail->SetAnimationIndex(AniIndex);
}

void cPlayer::Render(D3DXMATRIX* pMat)
{
	
	if (m_pBody)
		m_pBody->UpdateAndRender((D3DXMATRIXA16*)pMat);

	if (m_pFace)
	{
		m_pFace->m_matNeckTM = m_pBody->m_matNeckTM;
		m_pFace->UpdateAndRender();
	}
	
	if (m_pHair)
	{
		m_pHair->m_matHairTM = m_pBody->m_matHairTM;
		m_pHair->UpdateAndRender();
	}
	if (m_pTail)
	{
		m_pTail->m_matTailTM = m_pBody->m_matTaliTM;
		m_pTail->UpdateAndRender();
	}

	if (m_pRWeapon)
	{
		m_pRWeapon->Render(&m_pBody->m_matRWeaponTM);
		//m_pWeapon->Render();
	}
	if (m_pLWeapon)
	{
		m_pLWeapon->Render(&m_pBody->m_matLWeaponTM);
		//m_pWeapon->Render();
	}
	//if (m_pT)
	//{
	//	m_pT->m_matRWeaponTM = m_pBody->m_matRWeaponTM;
	//	m_pT->UpdateAndRender();
	//}
}

D3DXMATRIX * cPlayer::GetRootBone()
{
	return m_pBody->GetRootTM();
}

bool cPlayer::GetAniEnd(int _index)
{
	return m_pBody->GetAniEnd(_index);
}

float cPlayer::GetAniTime()
{
	return m_pBody->GetAniTime();
}

ST_SPHERE * cPlayer::GetRWeaponSphere()
{
	return m_pRWeapon->GetSphere();
}

ST_SPHERE * cPlayer::GetLWeaponSphere()
{
	return m_pLWeapon->GetSphere();
}

void cPlayer::SetRWeaponColor(D3DXCOLOR _color)
{
	m_pRWeapon->SetColor(_color);
}

void cPlayer::SetLWeaponColor(D3DXCOLOR _color)
{
	m_pLWeapon->SetColor(_color);
}
