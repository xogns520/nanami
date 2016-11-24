#include "stdafx.h"
#include "cEffect.h"



cEffect::cEffect()
	: m_filePath("")
	, m_bIsOn(false)
	, m_fAnimationSpeed(0.f)
	, m_fAlpha(0.f)
	, m_bIsSprite(false)
	, m_pSprite(NULL)
	, m_pMesh(NULL)
{
}


cEffect::~cEffect()
{
}


void cEffect::Destroy()
{
	
}


void cEffect::Setup(char* path, bool isSprite, float animationSpeed, float alpha)
{
	if (isSprite) {
		//스프라이트로 로딩하는 경우


	}
	else {
		//메쉬로 로딩하는 경우


	}
}

void cEffect::Update()
{

}

void cEffect::Render()
{

}
