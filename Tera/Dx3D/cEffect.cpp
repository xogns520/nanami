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
		//��������Ʈ�� �ε��ϴ� ���


	}
	else {
		//�޽��� �ε��ϴ� ���


	}
}

void cEffect::Update()
{

}

void cEffect::Render()
{

}
