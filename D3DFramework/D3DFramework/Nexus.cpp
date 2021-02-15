#include "stdafx.h"
#include "Nexus.h"
#include "SphereCollider.h"
#include "GameRenderer.h"
#include "DeferredStaticMeshRenderer.h"
Nexus::Nexus()
{
	transform->position = { 0,0,0 };
	transform->scale = { 0.00015f, 0.00015f, 0.00015f, };

	StaticMesh* mesh = RenderManager::CloneStaticMesh(L"sruap_ordernexus");

	
	
	AddComponent(L"StaticMesh", mesh);

	collider->SetRadius(2.6f);
	KST::DeferredStaticMeshRenderer* renderer =
		(KST::DeferredStaticMeshRenderer*)AddComponent<KST::DeferredStaticMeshRenderer>(L"renderer");
	renderer->SetMesh(mesh);
}

Nexus::~Nexus()
{

}
