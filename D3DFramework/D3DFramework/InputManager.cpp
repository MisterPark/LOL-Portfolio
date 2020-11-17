#include "stdafx.h"
#include "InputManager.h"

PKH::InputManager* pInputManager = nullptr;

PKH::InputManager::InputManager()
{
}

PKH::InputManager::~InputManager()
{
}

PKH::InputManager* InputManager::GetInstance()
{
	if (pInputManager == nullptr)
	{
		pInputManager = new InputManager();
	}

	return pInputManager;
}

void PKH::InputManager::Update()
{
	Clear();

	for (int i = 0; i < RANGE_OF_KEYS; i++)
	{
		SHORT keystate = GetAsyncKeyState(i);
		pInputManager->keys[i] = keystate & 0x8001;
		pInputManager->keyDowns[i] = keystate & 0x0001;
		pInputManager->keyUps[i] = keystate & 0x8000;
	}
	
}

void PKH::InputManager::Initialize()
{
	memset(pInputManager->keys, 0, RANGE_OF_KEYS);
	memset(pInputManager->keyDowns, 0, RANGE_OF_KEYS);
	memset(pInputManager->keyUps, 0, RANGE_OF_KEYS);

}

void PKH::InputManager::Destroy()
{
	delete pInputManager;
	pInputManager = nullptr;
}

void PKH::InputManager::Clear()
{
	memset(pInputManager->keys, 0, RANGE_OF_KEYS);
	memset(pInputManager->keyDowns, 0, RANGE_OF_KEYS);
	memset(pInputManager->keyUps, 0, RANGE_OF_KEYS);

	ClearMouseState();
}

void PKH::InputManager::ClearMouseState()
{
	int count = MaxOfEnum<Keys>();
	for (int i = 2; i < count; i++)
	{
		if (pInputManager->mouse[i])
		{
			pInputManager->mouseFrameCount[i]++;
			if (pInputManager->mouseFrameCount[i] == dfINPUT_LIFE_FRAME)
			{
				pInputManager->mouseFrameCount[i] = 0;
				pInputManager->mouse[i] = false;
			}
		}
	}
		

}

bool PKH::InputManager::GetKey(int _vkey)
{
	return pInputManager->keys[_vkey];
}

bool PKH::InputManager::GetKeyDown(int _vkey)
{
	return pInputManager->keyDowns[_vkey];
}

bool PKH::InputManager::GetKeyUp(int _vkey)
{
	return pInputManager->keyUps[_vkey];
}

bool PKH::InputManager::GetMouseLButton()
{
	return pInputManager->mouse[(int)Keys::LBUTTON];
}

bool PKH::InputManager::GetMouseLButtonUp()
{
	return pInputManager->mouse[(int)Keys::LBUTTON_UP];
}

bool PKH::InputManager::GetMouseLButtonDown()
{
	return pInputManager->mouse[(int)Keys::LBUTTON_DOWN];
}

bool PKH::InputManager::GetMouseLButtonDouble()
{
	return pInputManager->mouse[(int)Keys::LBUTTON_DOUBLE];
}

bool PKH::InputManager::GetMouseRButton()
{
	return pInputManager->mouse[(int)Keys::RBUTTON];
}

bool PKH::InputManager::GetMouseRButtonUp()
{
	return pInputManager->mouse[(int)Keys::RBUTTON_UP];
}

bool PKH::InputManager::GetMouseRButtonDown()
{
	return pInputManager->mouse[(int)Keys::RBUTTON_DOWN];
}

bool PKH::InputManager::GetMouseRButtonDouble()
{
	return pInputManager->mouse[(int)Keys::RBUTTON_DOUBLE];
}

bool PKH::InputManager::GetMouseWheelUp()
{
	return pInputManager->mouse[(int)Keys::WHEEL_UP];
}

bool PKH::InputManager::GetMouseWheelDown()
{
	return pInputManager->mouse[(int)Keys::WHEEL_DOWN];
}


POINT PKH::InputManager::GetMousePosOnClient()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hwnd, &pt);
	return pt;
}

POINT PKH::InputManager::GetMousePosOnWorld()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hwnd, &pt);

	pt.x += Camera::GetX();
	pt.y += Camera::GetY();

	return pt;
}
