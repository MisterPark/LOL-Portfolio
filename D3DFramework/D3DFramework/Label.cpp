#include "stdafx.h"
#include "Label.h"

Label::Label()
{
	foreColor = D3DCOLOR_ARGB(255, 0, 0, 0);
}

Label::~Label()
{
}

void Label::Initialize()
{
}

void Label::Release()
{
}

void Label::UpdateUI()
{
}

void Label::Update()
{
	UI::Update();
}

void Label::Render()
{
	RenderManager::DrawFont(text, transform->position, transform->scale, foreColor);
}
