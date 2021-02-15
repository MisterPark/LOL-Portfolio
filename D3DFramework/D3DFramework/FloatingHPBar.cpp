#include "stdafx.h"
#include "FloatingHPBar.h"
FloatingHPBar::FloatingHPBar()
{
	offset = { -0.2f,2.1f,-0.5f };

	mesh = (PKH::Rectangle*)AddComponent<PKH::Rectangle>(L"Mesh");
	mesh->SetTexture(L"bar_float (5)");
	mesh->SetBlendMode(BlendMode::ALPHA_TEST);

	Texture* tex = RenderManager::GetTexture(L"bar_float (5)");
	int w = tex->GetSpriteWidth();
	int h = tex->GetSpriteHeight();
	float scaleX = 0.8f;
	float scaleY = (float)h / w;
	transform->scale = { scaleX, scaleX *scaleY,1 };
}

FloatingHPBar::~FloatingHPBar()
{
	target = nullptr;
	mesh = nullptr;
}

void FloatingHPBar::Initialize()
{
}

void FloatingHPBar::Release()
{
}

void FloatingHPBar::Update()
{
	if (target->IsDestroy())
	{
		target = nullptr;
	}

	if (target != nullptr)
	{
		transform->position = target->transform->position + offset;
	}


	GameObject::Update();

	Billboard();
}

void FloatingHPBar::SetTarget(GameObject * target)
{
	this->target = target;
}
