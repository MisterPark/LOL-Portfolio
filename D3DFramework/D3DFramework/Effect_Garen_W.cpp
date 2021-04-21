#include "stdafx.h"
#include "Effect_Garen_W.h"
//#include "FogOfWarRenderer.h"

Effect_Garen_W::Effect_Garen_W()
{
	// wing
	CustomMesh* mesh = (CustomMesh*)GetComponent(L"Mesh");
	mesh->SetTexture(L"garen_base_w_wings");
	mesh->transform->position = { 0.f, 0.5f, 0.f };

	// wave
	Engine::Plane* meshWave = (Engine::Plane*)AddComponent<Engine::Plane>(L"MeshWave");
	meshWave->SetTexture(L"garen_base_w_energy_wave");
	ForwardRenderer* rendererWave = new ForwardRenderer{ this, L"./forward.fx" };
	rendererWave->SetMesh(meshWave);
	rendererWave->SetDiffuseTextureParam("g_diffuseTexture");
	rendererWave->SetPass(2);
	AddComponent(L"rendererWave", rendererWave);
}

Effect_Garen_W::~Effect_Garen_W()
{
}

void Effect_Garen_W::PostUpdate()
{
	StickToTarget();

	GameObject::PostUpdate();
}
