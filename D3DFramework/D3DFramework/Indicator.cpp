#include "stdafx.h"
#include "Indicator.h"
#include "Plane.h"
#include "Rectangle.h"

using namespace PKH;

Indicator::Indicator()
{
	Visible = false;

	PKH::Plane* mesh = (PKH::Plane*)AddComponent<PKH::Plane>(L"Mesh");
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
		transform->position = target->transform->position;
		transform->position.y += 0.1f;
		float range = target->GetAttackRange();
		transform->scale.x = range;
		transform->scale.z = range;

	}
	GameObject::Update();
}


void Indicator::SetTarget(Unit* _target)
{
	target = _target;
}
