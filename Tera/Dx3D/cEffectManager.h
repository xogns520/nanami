#pragma once

#define g_pEffectManager cEffectManager::GetInstance()

class cEffect;

class cEffectManager
{
private:
	char*									m_folderNm;
	std::map<std::string, cEffect*>	m_mapEffect;

	
public:
	SINGLETONE(cEffectManager);

	cEffect* GetEffect(std::string keyName);
	cEffect* PushEffect(std::string keyName, std::string fileName);

	void SetPosition(std::string keyName, D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPosition(std::string keyName);

	void Destroy();
};

