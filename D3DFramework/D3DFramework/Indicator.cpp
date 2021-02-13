#include "stdafx.h"
#include "Indicator.h"
#include "Plane.h"
#include "Rectangle.h"
#include "GameRenderer.h"
using namespace PKH;

Indicator::Indicator()
{
	isVisible = false;

	PKH::Plane* mesh = (PKH::Plane*)AddComponent<PKH::Plane>(L"Mesh");
	mesh->SetBlendMode(BlendMode::ALPHA_BLEND);
	mesh->SetTexture(L"circularrangeindicator");
	mesh->renderGroupID = RenderGroupID::AlphablendForward;
	GameRenderer::Register(mesh);
}

Indicator::~Indicator()
{
	target = nullptr;
	PKH::Plane* mesh = (PKH::Plane*)GetComponent(L"Mesh");
	GameRenderer::Unregister(mesh);
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

void Indicator::Render()
{
	GameObject::Render();
}

void Indicator::SetTarget(Unit* _target)
{
	target = _target;
}
