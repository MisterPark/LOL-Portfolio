#include "stdafx.h"
#include "Panel.h"

Panel::Panel()
{
	Initialize();
}

Panel::~Panel()
{
	Release();
}

void Panel::Initialize()
{
	transform->scale = { 3.f,3.f,1.f };
	textureKey = TextureKey::UI_BUTTON;

	UpdateUI();
}

void Panel::Release()
{

}

void Panel::UpdateUI()
{
	width = transform->scale.x * 88;
	height = transform->scale.y * 88;
}

void Panel::SetSize(int w, int h)
{
	transform->scale.x = float(w) / 88.f;
	transform->scale.y = float(h) / 88.f;
}
