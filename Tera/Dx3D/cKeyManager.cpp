#include "stdafx.h"
#include "cKeyManager.h"


cKeyManager::cKeyManager()
{
}


cKeyManager::~cKeyManager()
{
}

HRESULT cKeyManager::init()
{
	for (int i = 0; i < KEYMAX; i++)
	{
		this->_keyDown.set(i, false);
		this->_keyUp.set(i, false);
	}

	return S_OK;
}

void cKeyManager::Destroy()
{
}

bool cKeyManager::isOnceKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (!this->_keyDown[key])
		{
			this->_keyDown.set(key, true);
			return true;
		}
	}
	else this->_keyDown.set(key, false);

	return false;
}

bool cKeyManager::isOnceKeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) this->_keyUp.set(key, true);
	else
	{
		if (this->_keyUp[key])
		{
			this->_keyUp.set(key, false);
			return true;
		}
	}

	return false;
}

bool cKeyManager::isStayKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) return true;
	else return false;
}

bool cKeyManager::isToggleKey(int key)
{
	if (GetKeyState(key) & 0x0001) return true;
	else return false;
}
