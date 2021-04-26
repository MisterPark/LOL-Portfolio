#include "stdafx.h"
#include "Effect_Garen_R_GroundDecal.h"

Effect_Garen_R_GroundDecal::Effect_Garen_R_GroundDecal()
{
	CustomMesh* mesh = (CustomMesh*)GetComponent(L"Mesh");
	mesh->SetTexture(L"garen_base_r_ground_decal");
	offset = { 0.f,0.1f,0.f };
	transform->scale = { 2.f, 2.f, 2.f };
	
	auto renderer = dynamic_cast<ForwardRenderer*>(GetComponent(L"renderer"));
	if (renderer == nullptr) return;

	alpha = 0.f;
	renderer->SetAlpha(alpha);
}

Effect_Garen_R_GroundDecal::~Effect_Garen_R_GroundDecal()
{
}

void Effect_Garen_R_GroundDecal::PostUpdate()
{
	StickToTarget();
	EffectObject::PostUpdate();
}

void Effect_Garen_R_GroundDecal::Update()
{
	EffectObject::Update();
	
	auto renderer = dynamic_cast<ForwardRenderer*>(GetComponent(L"renderer"));
	if (renderer == nullptr) return;

	if (tick < 0.5) return;

	if (tick < 1.0) {
		alpha += 10 * Time::DeltaTime();
		if (alpha > 1.f) alpha = 1.f;
	}

	if (tick > 1.2) {
		alpha -= 1 * Time::DeltaTime();
		if (alpha < 0.f) alpha = 0.f;
	}

	renderer->SetAlpha(alpha);
}
