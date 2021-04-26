#include "stdafx.h"
#include "Effect_Garen_R_Distortion.h"
#include "DistortionRenderer.h"

Effect_Garen_R_Distortion::Effect_Garen_R_Distortion()
{
	//GetComponent(L"Mesh")->visible = false;
	GetComponent(L"renderer")->visible = false;

	offset = { 0.f,0.f,0.f };

	CustomMesh* mesh = (CustomMesh*)GetComponent(L"Mesh");

	Engine::DistortionRenderer* distortionRenderer = new Engine::DistortionRenderer(this);
	AddComponent(L"distortionRenderer", distortionRenderer);
	distortionRenderer->SetMesh(mesh);
	distortionRenderer->SetNoiseTexture(RenderManager::GetTexture(L"garen_distort-wave"));

	scale = 2.f;
}

Effect_Garen_R_Distortion::~Effect_Garen_R_Distortion()
{
}

void Effect_Garen_R_Distortion::PostUpdate()
{
	StickToTarget();
	EffectObject::PostUpdate();
}

void Effect_Garen_R_Distortion::Update()
{
	EffectObject::Update();

	Billboard();

	auto renderer = dynamic_cast<DistortionRenderer*>(GetComponent(L"distortionRenderer"));
	if (renderer == nullptr) return;

	renderer->SetOpacity(0);

	if (tick < 0.5f) return;

	scale += 6.f * Time::DeltaTime();
	transform->scale = { scale, scale, scale };

	renderer->SetOpacity(opacity);

	if (tick < 0.6f) return;

	opacity -= 0.8f * Time::DeltaTime();
	if (opacity < 0) opacity = 0;
	renderer->SetOpacity(opacity);
}
