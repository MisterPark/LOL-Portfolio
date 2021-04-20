#include "stdafx.h"
#include "Nexus.h"
#include "SphereCollider.h"
#include "DeferredStaticMeshRenderer.h"

Nexus::Nexus()
{
	transform->position = { 0,0,0 };
	transform->scale = { 0.00015f, 0.00015f, 0.00015f, };

	StaticMesh* mesh = RenderManager::CloneStaticMesh(L"sruap_ordernexus");

	
	
	AddComponent(L"StaticMesh", mesh);

	collider->SetRadius(2.6f);
	Engine::DeferredStaticMeshRenderer* renderer =
		(Engine::DeferredStaticMeshRenderer*)AddComponent<Engine::DeferredStaticMeshRenderer>(L"renderer");
	renderer->SetMesh(mesh);
}

Nexus::~Nexus()
{

}

void Nexus::OnDamaged(Unit* target, Skill* targetSkill, float* damage)
{
	bool invinCheck = false;

	for (auto& building : frontBuildingList)
	{
		if (!building->IsDead()) {
			invinCheck = true;
			break;
		}
	}
	
	if (invinCheck)
		*damage = 0.f;
}
