#pragma once

#include "iMap.h"

class cGroup;

class cWeapon : public iMap
{
private:
	std::vector<cGroup*>		m_vecGroup;
	std::vector<D3DXVECTOR3>	m_vecSurface;

public:
	cWeapon(void);
	virtual ~cWeapon(void);

	void Load(char* szMap, D3DXMATRIXA16* pmat);
	virtual void Load(char* szMap, char* szSurface, D3DXMATRIXA16* pmat);

	// iMap override
	virtual bool GetHeight(IN float x, OUT float& y, IN float z) override;
	virtual void Render() override;
	virtual void Render(D3DXMATRIX* pMat);
};

