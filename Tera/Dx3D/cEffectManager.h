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
	cEffect* PushSpriteEffect(std::string keyName, std::string fileName);
	cEffect* PushMeshEffect(std::string keyName, std::string fileName, std::string shaderPath);

	//애니메이션 속도나 알파값같은것도 세팅 필요할 것 같음
	void		SetPosition(std::string keyName, D3DXVECTOR3 pos);
	void		SetSize(std::string keyName, float size);

	D3DXVECTOR3 GetPosition(std::string keyName);
	float		GetSize(std::string keyName);

	void Render(std::string keyName);

	void Destroy();
};

