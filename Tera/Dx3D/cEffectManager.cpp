#include "stdafx.h"
#include "cEffectManager.h"
#include "cEffect.h"


cEffectManager::cEffectManager(void)
{
	m_folderNm = "./Tera/Effects";

}

cEffectManager::~cEffectManager(void)
{
}

//void cEffectManager::Destroy() 
//{
//	for each(auto it in m_mapEffect)
//	{
//		it.second->Destroy();
//		SAFE_DELETE(it.second);
//	}
//}
//
//cSkinnedMesh* cEffectManager::GetEffect(char* szFolder, char* szFilename)
//{
//	std::string sFullPath(szFolder);
//	sFullPath += std::string(szFilename);
//
//	if (m_mapEffect.find(sFullPath) == m_mapEffect.end())
//	{
//		cSkinnedMesh* pSkinnedMesh = new cSkinnedMesh();
//		pSkinnedMesh->Load(szFolder, szFilename);
//		m_mapEffect[sFullPath] = pSkinnedMesh;
//	}
//	return m_mapEffect[sFullPath];
//}


cEffect* cEffectManager::GetEffect(std::string keyName) {
	return m_mapEffect[keyName];
}


cEffect* cEffectManager::PushEffect(std::string keyName, std::string fileName, bool isSprite)
{
	if (m_mapEffect.find(keyName) == m_mapEffect.end()) {
		m_mapEffect[keyName] = new cEffect;
		m_mapEffect[keyName]->Setup((char*)fileName.c_str(), isSprite, NULL, 1.0f);		//animationspeed alpha 수정될 수 있음
	}

	return m_mapEffect[keyName];
}


void cEffectManager::SetPosition(std::string keyName, D3DXVECTOR3 pos)
{
	if (m_mapEffect.find(keyName) != m_mapEffect.end()) {
		m_mapEffect[keyName]->SetCenter(pos);
	}
}

D3DXVECTOR3 cEffectManager::GetPosition(std::string keyName)
{
	D3DXVECTOR3 t = D3DXVECTOR3(0, 0, 0);
	if (m_mapEffect.find(keyName) != m_mapEffect.end()) {
		t = m_mapEffect[keyName]->GetPosition();

		//이것도 vector아니고 matrix로 바꿔야할수있음!! 확인해볼것
	}
	return t;
}

void cEffectManager::SetSize(std::string keyName, float size)
{
	if (m_mapEffect.find(keyName) != m_mapEffect.end()) {
		D3DXMATRIXA16 matT;
		D3DXMatrixIdentity(&matT);
		D3DXMatrixScaling(&matT, size, size, size);

		m_mapEffect[keyName]->SetSpriteSize(matT);
	}
}

ST_SIZE cEffectManager::GetSize(std::string keyName)
{
	ST_SIZE t;

	//RECT크기를 반환하면 안됨!!!!
	//if (m_mapEffect.find(keyName) != m_mapEffect.end()) {
	//	RECT* rc = m_mapEffect[keyName]->GetSpriteRectRef();
	//	t.fWidth = rc->right - rc->left;
	//	t.fWidth = rc->bottom - rc->top;
	//}

	return t;
}

void cEffectManager::Render(std::string keyName)
{
	if (m_mapEffect.find(keyName) == m_mapEffect.end()) {
		m_mapEffect[keyName]->Render();
	}
}

