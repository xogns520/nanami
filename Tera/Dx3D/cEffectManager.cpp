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


cEffect* cEffectManager::PushEffect(std::string keyName, std::string fileName)
{
	if (m_mapEffect.find(keyName) == m_mapEffect.end()) {
		char* t = new char[fileName.length() + 1];
		strcpy(t, fileName.c_str());
		
		m_mapEffect[keyName];

		//m_mapEffect[keyName] = g_pSkinnedMeshManager->GetSkinnedMesh(m_folderNm, t);

		delete[] t;
	}

	return m_mapEffect[keyName];
}


void cEffectManager::SetPosition(std::string keyName, D3DXVECTOR3 pos)
{
	if (m_mapEffect.find(keyName) == m_mapEffect.end()) {

	}

}

D3DXVECTOR3 cEffectManager::GetPosition(std::string keyName)
{

	return D3DXVECTOR3(0, 0, 0);
}