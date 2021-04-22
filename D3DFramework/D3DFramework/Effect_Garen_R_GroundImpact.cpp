#include "stdafx.h"
#include "Effect_Garen_R_GroundImpact.h"

Effect_Garen_R_GroundImpact::Effect_Garen_R_GroundImpact()
{
	CustomMesh* mesh = (CustomMesh*)GetComponent(L"Mesh");
	mesh->SetTexture(L"garen_base_r_impact_dome");

	transform->scale = { 1.f, 1.f, 1.f };

	auto renderer = dynamic_cast<ForwardRenderer*>(GetComponent(L"renderer"));
	if (renderer == nullptr) return;

	renderer->SetPass(2);
}

Effect_Garen_R_GroundImpact::~Effect_Garen_R_GroundImpact()
{
}

void Effect_Garen_R_GroundImpact::PostUpdate()
{
	StickToTarget();
	EffectObject::PostUpdate();
}

void Effect_Garen_R_GroundImpact::Update()
{
	EffectObject::Update();

	auto renderer = dynamic_cast<ForwardRenderer*>(GetComponent(L"renderer"));
	if (renderer == nullptr) return;

	visible = false;

	if (tick < 0.5) return;

	visible = true;

	scale += 2 * Time::DeltaTime();
	transform->scale = { scale, scale, scale };
	
	if (tick < 0.9) return;

	alpha -= 5 * Time::DeltaTime();
}
