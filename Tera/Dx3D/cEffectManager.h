#pragma once

#define g_pEffectManager cEffectManager::GetInstance()

class cEffect;

class cEffectManager
{
private:
	char*							m_folderNm;
	std::map<std::string, cEffect*>	m_mapEffect;

	
public:
	SINGLETONE(cEffectManager);

	cEffect* GetEffect(std::string keyName);
	cEffect* PushEffect(std::string keyName, std::string fileName, bool isSprite);

	//애니메이션 속도나 알파값같은것도 세팅 필요할 것 같음
	void		SetPosition(std::string keyName, D3DXVECTOR3 pos);
	void		SetSize(std::string keyName, float size);

	D3DXVECTOR3 GetPosition(std::string keyName);
	ST_SIZE		GetSize(std::string keyName);
		
	void Render(std::string keyName);

	void Destroy();
};

