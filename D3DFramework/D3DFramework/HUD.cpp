#include "stdafx.h"
#include "HUD.h"

HUD::HUD()
	: UI()
{
}

HUD::HUD(const std::wstring& _key)
	: UI()
{
	SetTexture(_key);
	SetSizeByTexture();
	SetLocation(0.f, 0.f);
}

HUD::HUD(const std::wstring& _key, Vector2 _pos)
	: UI()
{
	SetTexture(_key);
	SetSizeByTexture();
	SetLocation(_pos);
}

HUD::~HUD()
{
}

void HUD::Initialize()
{
}

void HUD::Release()
{
}
