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
	distortionRenderer->SetNoiseTexture(RenderManager::GetTexture(L"garen_distort-twirl"));
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
	Vector3 before, after;
	EffectObject::Update();

	Billboard();


	//scale += 1 * Time::DeltaTime();
	//transform->scale = { scale, scale, scale };
}
