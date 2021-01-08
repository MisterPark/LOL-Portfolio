#include "stdafx.h"
#include "UI_Spell.h"

UI_Spell::UI_Spell()
{
	SetTexture(L"summoner_flash");
	mesh->SetBlendMode(BlendMode::ALPHA_BLEND);
}

UI_Spell::~UI_Spell()
{
}

void UI_Spell::Initialize()
{
}

void UI_Spell::Release()
{
}
