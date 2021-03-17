﻿#include "stdafx.h"
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

	shieldBar = (Bar*)CreateChild(L"bar_float (3)", Vector2(26, 6));
	shieldBar->transform->scale = { 0.97f,1.f,1.f };

	overShieldBar = (Bar*)CreateChild(L"bar_float (4)", Vector2(26, 6));
	overShieldBar->transform->scale = { 0.97f,1.f,1.f };
	
	nickLabel = new Label(22);
	nickLabel->SetLocation(10, -25);
	AddChild(L"Nickname", nickLabel);

	//textOffsetPosition = { 0,-35,0 };
}

FloatingBar::~FloatingBar()
{
	target = nullptr;
	hpBar = nullptr;
	mpBar = nullptr;
	shieldBar = nullptr;
	overShieldBar = nullptr;
	nickLabel = nullptr;
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
		visible = !target->IsDead();

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
		Vector2 shieldRatio = { 0,1 };
		Vector2 overShieldRatio = { 0,1 };
		float hp = target->stat->GetValue(StatType::Health);
		float mp = target->stat->GetValue(StatType::Mana);
		float maxHp = target->stat->GetValue(StatType::MaxHealth);
		float maxMp = target->stat->GetValue(StatType::MaxMana);
		float shield = target->stat->GetValue(StatType::Shield);
		float overShield = 0.f;

		if (maxHp != 0)
		{
			hpRatio.x = hp / maxHp;
			if (shield > 0)
			{
				// 초과실드 = 체력 + 실드 - 최대체력
				overShield = (hp + shield) - maxHp;
				// 실드 = 총 실드량 - 초과실드
				if (overShield > 0)
				{
					shield = shield - overShield;
				}
				// 실드 비율
				shieldRatio.x = shield / maxHp;
				overShieldRatio.x = overShield / maxHp;
			}
		}
		if (maxMp != 0)
		{
			mpRatio.x = mp / maxMp;
		}

		hpBar->uvRatio = hpRatio;
		mpBar->uvRatio = mpRatio;
		shieldBar->uvRatio = shieldRatio;
		overShieldBar->uvRatio = overShieldRatio;

		// hp바 끝위치 = hp바 시작위치 + (hp바 가로비율 * hp바 가로크기)
		float hpEndX = hpBar->transform->position.x + (hpBar->uvRatio.x * (hpBar->texture->GetSpriteWidth() * hpBar->transform->scale.x));
		// 실드위치 = 현재 체력 위치
		shieldBar->transform->position.x = hpEndX;
		// 초과실드 위치 = 현재 체력위치 - 초과실드 가로크기
		overShieldBar->transform->position.x = hpEndX - (overShieldRatio.x * (overShieldBar->texture->GetSpriteWidth() * overShieldBar->transform->scale.x));
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
	nickLabel->text = _nick;
}
