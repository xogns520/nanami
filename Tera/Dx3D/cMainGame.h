#pragma once

class cCamera;
class cGrid;
class cCharController;
class iMap;
class cSkinnedMesh;
class cPlayer;
class cSkyBox;

class cEffect;

class cMap;
class cMapSkinnedMesh;


class cMainGame
{
private:
	cCamera*					m_pCamera;
	cGrid*						m_pGrid;
	cCharController*			m_pCharController;
	iMap*						m_pMap;
	std::vector<cSkinnedMesh*>	m_vecSkinnedMesh;

	cPlayer*					m_pPlayer;
	cPlayer*					m_pPlayerDash;
	cSkyBox*					m_pSkyBox;

	iMap*						m_pField;
	iMap*						m_pWall;
	iMap*						m_pGate1;
	iMap*						m_pGate2;
	
	cMap*						m_RealMap;
	cMapSkinnedMesh*			m_pTerrain;

	std::vector<cEffect*>		m_vecEffect;
	
	
public:
	cMainGame(void);
	~cMainGame(void);

	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void SetLight();
};

