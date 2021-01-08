#include "stdafx.h"
#include "FloatingBar.h"

FloatingBar::FloatingBar()
{
	mesh = (PKH::Rectangle*)AddComponent<PKH::Rectangle>(L"Mesh");
	mesh->SetTexture(L"border_float (1)");
	mesh->SetBlendMode(BlendMode::ALPHA_TEST);
	
	offset = { 0,2,-0.5f };

	Texture* tex = RenderManager::GetTexture(L"border_float (1)");
	int w = tex->GetSpriteWidth();
	int h = tex->GetSpriteHeight();
	float scaleY = (float)h / w;
	transform->scale = { 1,scaleY,1 };
}

FloatingBar::~FloatingBar()
{
	target = nullptr;
	mesh = nullptr;
}

void FloatingBar::Initialize()
{
}

void FloatingBar::Release()
{
}

void FloatingBar::Update()
{
	if (target->IsDead())
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

void FloatingBar::SetTarget(GameObject* target)
{
	this->target = target;
}
