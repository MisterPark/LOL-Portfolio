#include "stdafx.h"
#include "TurretFloatingBar.h"

TurretFloatingBar::TurretFloatingBar()
{
	// 170,15
	// 11,6
	offset = { 0.f,3.5f, 0.f };
	offset2 = { -84,-11,0 };

	Texture* tex = RenderManager::GetTexture(textureKeyHP);
	int w = tex->GetSpriteWidth();
	int h = tex->GetSpriteHeight();
	float ratioW = 170.f / w;
	float ratioH = 15.f / h;
	scaleHP = { ratioW,ratioH,1.f };
	SetTexture(L"border_float (2)");
}

TurretFloatingBar::~TurretFloatingBar()
{
}

