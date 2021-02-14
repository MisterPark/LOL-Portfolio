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

void TurretFloatingBar::Render()
{
	float ratioHP = 0.f;

	RenderManager::DrawSprite(textureKey, *transform, 0);
	if (target != nullptr)
	{
		ratioHP = (float)target->stat->hp.GetValue() / target->stat->maxHp.GetValue();
	}
	if (ratioHP < 0.f)
	{
		ratioHP = 0.f;
	}
	RenderManager::DrawUIHorizontal(textureKeyHP, transform->position + offset2, scaleHP, 0, ratioHP);
}
