#include "stdafx.h"
#include "cEffect.h"
#include "cSkinnedMeshManager.h"


cEffect::cEffect()
{
	m_folderNm = "./Tera/Effects";

	//임시
	LoadEffects();
}


cEffect::~cEffect()
{
}


void cEffect::Destroy()
{
	for each (auto m in m_mapEffect)
	{
		SAFE_DELETE(m.second);
	}
}


void cEffect::LoadEffects()
{
	//effect목록 추가

	PushEffect("fileBall", "EffectFireball.X");
}

cSkinnedMesh* cEffect::GetEffect(std::string keyName) {
	return m_mapEffect[keyName];
}


cSkinnedMesh* cEffect::PushEffect(std::string keyName, std::string fileName)
{
	if (m_mapEffect.find(keyName) == m_mapEffect.end()) {
		char* t = new char[fileName.length() + 1];
		strcpy(t, fileName.c_str());
		
		m_mapEffect[keyName] = g_pSkinnedMeshManager->GetSkinnedMesh(m_folderNm, t);

		delete[] t;
	}
	
	return m_mapEffect[keyName];
}


void cEffect::SetPosition(std::string keyName, D3DXVECTOR3 pos)
{
	if (m_mapEffect.find(keyName) == m_mapEffect.end()) {

	}

}

D3DXVECTOR3 cEffect::GetPosition(std::string keyName)
{

	return D3DXVECTOR3(0, 0, 0);
}