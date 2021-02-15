#include "stdafx.h"
#include "MinionFloatingBar.h"

MinionFloatingBar::MinionFloatingBar()
{
	// 64,5
	// 1,1
	offset = { 0.f,1.5f, 0.f };
	offset2 = { -32,-2,0 };

	Texture* tex = RenderManager::GetTexture(textureKeyHP);
	int w = tex->GetSpriteWidth();
	int h = tex->GetSpriteHeight();
	float ratioW = 64.f / w;
	float ratioH = 5.f / h;
	scaleHP = { ratioW,ratioH,1.f };
	SetTexture(L"border_float (6)");
}

MinionFloatingBar::~MinionFloatingBar()
{
}