#include "stdafx.h"
#include "Inhibitor.h"
#include "SphereCollider.h"
#include "DeferredStaticMeshRenderer.h"

Inhibitor::Inhibitor()
{
	transform->position = { 0,0,0 };
	transform->scale = { 0.00018f, 0.00018f, 0.00018f, };

	StaticMesh* mesh = RenderManager::CloneStaticMesh(L"sruap_orderinhibitor");
	AddComponent(L"StaticMesh", mesh);

	collider->SetRadius(1.5f);
	Engine::DeferredStaticMeshRenderer* renderer =
		(Engine::DeferredStaticMeshRenderer*)AddComponent<Engine::DeferredStaticMeshRenderer>(L"renderer");
	renderer->SetMesh(mesh);
}

Inhibitor::~Inhibitor()
{
}
