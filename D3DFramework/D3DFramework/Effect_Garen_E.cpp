#include "stdafx.h"
#include "Effect_Garen_E.h"
#include "FogOfWarRenderer.h"

Effect_Garen_E::Effect_Garen_E()
{
	RemoveComponent(L"Mesh");

	StaticMesh* mesh = RenderManager::CloneStaticMesh(L"garen_base_e_spin");
	AddComponent(L"StaticMesh", mesh);
	Engine::DeferredStaticMeshRenderer* renderer =
		(Engine::DeferredStaticMeshRenderer*)AddComponent<Engine::DeferredStaticMeshRenderer>(L"renderer");

	renderer->SetMesh(mesh);
	renderer->EnableRimLight({ 0.f, 0.f, 1.f });
}

Effect_Garen_E::~Effect_Garen_E()
{
}
