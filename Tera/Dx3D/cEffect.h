#pragma once
#include"cSkinnedMesh.h"


class cEffect
{
private :
	char*									m_folderNm;
	std::map<std::string, cSkinnedMesh*>	m_mapEffect;

	
public :
	cEffect();
	~cEffect();

	cSkinnedMesh* GetEffect(std::string keyName);
	cSkinnedMesh* PushEffect(std::string keyName, std::string fileName);

	void SetPosition(std::string keyName, D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPosition(std::string keyName);


	void Destroy();
private:
	void LoadEffects();

};

