#include "stdafx.h"
#include "FloatingBar.h"
#include "Bar.h"
#include "Label.h"

FloatingBar::FloatingBar()
{

	offset = { 0,1.8f,-0.5f };

	SetTexture(L"border_float (1)");
	SetSizeByTexture();

	hpBar = (Bar*)CreateChild(L"bar_float (2)", Vector2(26, 6));
	hpBar->transform->scale = { 0.97f,1.f,1.f };
	
	mpBar = (Bar*)CreateChild(L"bar_float (5)", Vector2(26, 20));
	mpBar->transform->scale = { 0.97f,0.3f,1.f };
	

	//textOffsetPosition = { 0,-35,0 };
}

FloatingBar::~FloatingBar()
{
	target = nullptr;
	hpBar = nullptr;
	mpBar = nullptr;
}

void FloatingBar::Update()
{
	
	GameObject::Update();
}

void FloatingBar::PostUpdate()
{
	if (target != nullptr)
	{
		if (target->IsDestroy())
		{
			target = nullptr;
		}
	}

	if (target != nullptr)
	{
		isVisible = !target->IsDead();

		Vector3 worldPos = target->transform->position + offset;
		worldPos = Camera::main->WorldToScreenPoint(worldPos);

		Vector2 offset;
		if (texture != nullptr)
		{
			offset.x = -texture->GetSpriteWidth() * 0.5f;
			offset.y = -texture->GetSpriteHeight() * 0.5f;
		}
		SetLocation(worldPos.x + offset.x, worldPos.y + offset.y);

		Vector2 hpRatio = { 0,1 };
		Vector2 mpRatio = { 0,1 };
		float hp = target->GetHP();
		float mp = target->GetMP();
		float maxHp = target->GetMaxHP();
		float maxMp = target->GetMaxMP();

		if (maxHp != 0)
		{
			hpRatio.x = hp / maxHp;
		}
		if (maxMp != 0)
		{
			mpRatio.x = mp / maxMp;
		}
		if (hp != maxHp)
		{
			int a = 10;
		}

		hpBar->uvRatio = hpRatio;
		mpBar->uvRatio = mpRatio;
	}


	GameObject::PostUpdate();
}

void FloatingBar::SetTarget(Unit* target)
{
	this->target = target;
}

void FloatingBar::SetTextureHP(const wstring& _key)
{
	hpBar->SetTexture(_key);
}

void FloatingBar::SetTextureMP(const wstring& _key)
{
	mpBar->SetTexture(_key);
}

void FloatingBar::SetNickname(const wstring& _nick)
{
	
}
