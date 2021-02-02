#include "stdafx.h"
#include "Nexus.h"
#include "SphereCollider.h"

Nexus::Nexus()
{
	transform->position = { 0,0,0 };
	transform->scale = { 0.00015f, 0.00015f, 0.00015f, };

	StaticMesh* mesh = RenderManager::CloneStaticMesh(L"sruap_ordernexus");
	AddComponent(L"StaticMesh", mesh);

	collider->SetRadius(2.6f);
}

Nexus::~Nexus()
{
}
