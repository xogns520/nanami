#pragma once
#include"cSkinnedMesh.h"


class cEffect
{
private :
	std::map<std::string, cSkinnedMesh*>	m_mapEffect;

	
public :
	cEffect();
	~cEffect();

	void PushEffect(std::string keyName, cSkinnedMesh* effect);
	cSkinnedMesh* GetEffect(std::string keyName);

	void Destroy();
private:
	void LoadEffects();

};

