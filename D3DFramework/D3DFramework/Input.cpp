#include "stdafx.h"
#include "Input.h"

Engine::Input* pInput = nullptr;

Engine::Input::Input()
{
}

Engine::Input::~Input()
{
}

Engine::Input* Input::GetInstance()
{
	if (pInput == nullptr)
	{
		pInput = new Input();
	}

	return pInput;
}

void Engine::Input::Update()
{
	Clear();

	for (int i = 0; i < RANGE_OF_KEYS; i++)
	{
		SHORT keystate = GetAsyncKeyState(i);
		pInput->keys[i] = keystate & 0x8001;
		pInput->keyDowns[i] = keystate & 0x0001;
		pInput->keyUps[i] = keystate & 0x8000;
	}
	
}

void Engine::Input::Initialize()
{
	memset(pInput->keys, 0, RANGE_OF_KEYS);
	memset(pInput->keyDowns, 0, RANGE_OF_KEYS);
	memset(pInput->keyUps, 0, RANGE_OF_KEYS);

}

void Engine::Input::Destroy()
{
	delete pInput;
	pInput = nullptr;
}

void Engine::Input::Clear()
{
	memset(pInput->keys, 0, RANGE_OF_KEYS);
	memset(pInput->keyDowns, 0, RANGE_OF_KEYS);
	memset(pInput->keyUps, 0, RANGE_OF_KEYS);

	ClearMouseState();
}

void Engine::Input::ClearMouseState()
{
	int count = MaxOfEnum<Keys>();
	for (int i = 2; i < count; i++)
	{
		if (pInput->mouse[i])
		{
			pInput->mouseFrameCount[i]++;
			if (pInput->mouseFrameCount[i] == dfINPUT_LIFE_FRAME)
			{
				pInput->mouseFrameCount[i] = 0;
				pInput->mouse[i] = false;
			}
		}
	}
		

}

bool Engine::Input::GetKey(int _vkey)
{
	return pInput->keys[_vkey];
}

bool Engine::Input::GetKeyDown(int _vkey)
{
	return pInput->keyDowns[_vkey];
}

bool Engine::Input::GetKeyUp(int _vkey)
{
	return pInput->keyUps[_vkey];
}

bool Engine::Input::GetMouseLButton()
{
	return pInput->mouse[(int)Keys::LBUTTON];
}

bool Engine::Input::GetMouseLButtonUp()
{
	return pInput->mouse[(int)Keys::LBUTTON_UP];
}

bool Engine::Input::GetMouseLButtonDown()
{
	return pInput->mouse[(int)Keys::LBUTTON_DOWN];
}

bool Engine::Input::GetMouseLButtonDouble()
{
	return pInput->mouse[(int)Keys::LBUTTON_DOUBLE];
}

bool Engine::Input::GetMouseRButton()
{
	return pInput->mouse[(int)Keys::RBUTTON];
}

bool Engine::Input::GetMouseRButtonUp()
{
	return pInput->mouse[(int)Keys::RBUTTON_UP];
}

bool Engine::Input::GetMouseRButtonDown()
{
	return pInput->mouse[(int)Keys::RBUTTON_DOWN];
}

bool Engine::Input::GetMouseRButtonDouble()
{
	return pInput->mouse[(int)Keys::RBUTTON_DOUBLE];
}

bool Engine::Input::GetMouseWheelUp()
{
	return pInput->mouse[(int)Keys::WHEEL_UP];
}

bool Engine::Input::GetMouseWheelDown()
{
	return pInput->mouse[(int)Keys::WHEEL_DOWN];
}

Vector3 Engine::Input::GetMousePosition()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hwnd, &pt);
	
	Vector3 point = { (float)pt.x,(float)pt.y,0 };
	return point;
}