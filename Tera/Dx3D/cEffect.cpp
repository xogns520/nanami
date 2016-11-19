#include "stdafx.h"
#include "cEffect.h"



cEffect::cEffect()
{
	
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


void LoadEffects()
{

}

void PushEffect(std::string keyName, cSkinnedMesh* effect)
{

}

cSkinnedMesh* GetEffect(std::string keyName)
{
	cSkinnedMesh* temp;
	
	return temp;
}