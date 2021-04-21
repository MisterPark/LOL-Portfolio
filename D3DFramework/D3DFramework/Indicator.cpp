#include "stdafx.h"
#include "Indicator.h"
#include "Plane.h"
#include "Rectangle.h"

using namespace Engine;

Indicator::Indicator()
{
	visible = false;

	Engine::Plane* mesh = (Engine::Plane*)AddComponent<Engine::Plane>(L"Mesh");
	mesh->SetBlendMode(BlendMode::ALPHA_BLEND);
	mesh->SetTexture(L"circularrangeindicator");

}

Indicator::~Indicator()
{
	target = nullptr;

}

void Indicator::Initialize()
{
}

void Indicator::Release()
{
}

void Indicator::Update()
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
		if (target->stat == nullptr)
		{
			target = nullptr;
		}
	}

	if (target != nullptr)
	{
		transform->position = target->transform->position;
		transform->position.y += 0.1f;
		float range = target->stat->GetValue(StatType::Range);
		transform->scale.x = range;
		transform->scale.z = range;

	}
	GameObject::Update();
}


void Indicator::SetTarget(Unit* _target)
{
	target = _target;
}
