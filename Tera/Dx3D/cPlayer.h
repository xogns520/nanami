#pragma once

class cBody;
class cFace;
class cHair;
class cWeapon;
class iMap;

class cPlayer
{
private:
	cBody* m_pBody;
	cFace* m_pFace;
	cHair* m_pHair;
	iMap* m_pMap;
	cWeapon* m_pWeapon;
public:
	cPlayer();
	~cPlayer();

	void Setup(char* Directory, char* PathBody, char* PathFace, char* PathHair);
	void Render(D3DXMATRIX* pMat);
};

