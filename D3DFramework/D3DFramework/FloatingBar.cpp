#include "stdafx.h"
#include "FloatingBar.h"

FloatingBar::FloatingBar()
{
	offset = { 0,2,-0.5f };

	mesh = (PKH::Rectangle*)AddComponent<PKH::Rectangle>(L"Mesh");
	mesh->SetTexture(L"border_float (1)");
	mesh->SetBlendMode(BlendMode::ALPHA_TEST);

	Texture* tex = RenderManager::GetTexture(L"border_float (1)");
	int w = tex->GetSpriteWidth();
	int h = tex->GetSpriteHeight();
	float scaleY = (float)h / w;
	transform->scale = { 1,scaleY,1 };

}

FloatingBar::~FloatingBar()
{
	target = nullptr;
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
		//Vector3 pos = target->transform->position;// +offset;

		//Vector3 screenPos = Camera::main->WorldToScreenPoint(pos);

		//transform->position = screenPos;
		//Vector3 screenPos = target->transform->position + offset;
		//SetLocation(screenPos.x, screenPos.y);
		
		//transform->position = target->transform->position;
	}
	
	UI::Update();
	//GameObject::Update();

	//Billboard();

	
}

void FloatingBar::Render()
{
	UI::Render();
}

void FloatingBar::SetTarget(GameObject* target)
{
	this->target = target;
}
