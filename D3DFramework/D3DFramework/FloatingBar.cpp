#include "stdafx.h"
#include "FloatingBar.h"
#include "Bar.h"
#include "Label.h"

FloatingBar::FloatingBar()
{

	offset = { 0,1.8f,-0.5f };

	SetTexture(L"border_float (1)");
	SetSizeByTexture();

	hp = (Bar*)AddChild(L"bar_float (2)", Vector2(26, 6));
	hp->transform->scale = { 0.97f,1.f,1.f };
	
	mp = (Bar*)AddChild(L"bar_float (5)", Vector2(26, 20));
	mp->transform->scale = { 0.97f,0.3f,1.f };
	

	//textOffsetPosition = { 0,-35,0 };
}

FloatingBar::~FloatingBar()
{
	target = nullptr;
	hp = nullptr;
	mp = nullptr;
}

void FloatingBar::Update()
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
	}

	
	
	GameObject::Update();
}

void FloatingBar::SetTarget(Unit* target)
{
	this->target = target;
}

void FloatingBar::SetTextureHP(const wstring& _key)
{
	hp->SetTexture(_key);
}

void FloatingBar::SetTextureMP(const wstring& _key)
{
	mp->SetTexture(_key);
}

void FloatingBar::SetNickname(const wstring& _nick)
{
	
}
