#include "stdafx.h"
#include "Nexus.h"
#include "SphereCollider.h"
#include "GameRenderer.h"
Nexus::Nexus()
{
	transform->position = { 0,0,0 };
	transform->scale = { 0.00015f, 0.00015f, 0.00015f, };

	StaticMesh* mesh = RenderManager::CloneStaticMesh(L"sruap_ordernexus");
	AddComponent(L"StaticMesh", mesh);

	collider->SetRadius(2.6f);
	mesh->renderGroupID = RenderGroupID::Deferred;
	GameRenderer::Register(mesh);
}

Nexus::~Nexus()
{
	StaticMesh* mesh = (StaticMesh*)GetComponent(L"StaticMesh");
	GameRenderer::Unregister(mesh);
}
