#include "stdafx.h"
#include "InputManager.h"

Engine::InputManager* pInputManager = nullptr;

Engine::InputManager::InputManager()
{
}

Engine::InputManager::~InputManager()
{
}

Engine::InputManager* InputManager::GetInstance()
{
	if (pInputManager == nullptr)
	{
		pInputManager = new InputManager();
	}

	return pInputManager;
}

void Engine::InputManager::Update()
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

void Engine::InputManager::Initialize()
{
	memset(pInputManager->keys, 0, RANGE_OF_KEYS);
	memset(pInputManager->keyDowns, 0, RANGE_OF_KEYS);
	memset(pInputManager->keyUps, 0, RANGE_OF_KEYS);

}

void Engine::InputManager::Destroy()
{
	delete pInputManager;
	pInputManager = nullptr;
}

void Engine::InputManager::Clear()
{
	memset(pInputManager->keys, 0, RANGE_OF_KEYS);
	memset(pInputManager->keyDowns, 0, RANGE_OF_KEYS);
	memset(pInputManager->keyUps, 0, RANGE_OF_KEYS);

	ClearMouseState();
}

void Engine::InputManager::ClearMouseState()
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

bool Engine::InputManager::GetKey(int _vkey)
{
	return pInputManager->keys[_vkey];
}

bool Engine::InputManager::GetKeyDown(int _vkey)
{
	return pInputManager->keyDowns[_vkey];
}

bool Engine::InputManager::GetKeyUp(int _vkey)
{
	return pInputManager->keyUps[_vkey];
}

bool Engine::InputManager::GetMouseLButton()
{
	return pInputManager->mouse[(int)Keys::LBUTTON];
}

bool Engine::InputManager::GetMouseLButtonUp()
{
	return pInputManager->mouse[(int)Keys::LBUTTON_UP];
}

bool Engine::InputManager::GetMouseLButtonDown()
{
	return pInputManager->mouse[(int)Keys::LBUTTON_DOWN];
}

bool Engine::InputManager::GetMouseLButtonDouble()
{
	return pInputManager->mouse[(int)Keys::LBUTTON_DOUBLE];
}

bool Engine::InputManager::GetMouseRButton()
{
	return pInputManager->mouse[(int)Keys::RBUTTON];
}

bool Engine::InputManager::GetMouseRButtonUp()
{
	return pInputManager->mouse[(int)Keys::RBUTTON_UP];
}

bool Engine::InputManager::GetMouseRButtonDown()
{
	return pInputManager->mouse[(int)Keys::RBUTTON_DOWN];
}

bool Engine::InputManager::GetMouseRButtonDouble()
{
	return pInputManager->mouse[(int)Keys::RBUTTON_DOUBLE];
}

bool Engine::InputManager::GetMouseWheelUp()
{
	return pInputManager->mouse[(int)Keys::WHEEL_UP];
}

bool Engine::InputManager::GetMouseWheelDown()
{
	return pInputManager->mouse[(int)Keys::WHEEL_DOWN];
}

Vector3 Engine::InputManager::GetMousePosition()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hwnd, &pt);
	
	Vector3 point = { (float)pt.x,(float)pt.y,0 };
	return point;
}