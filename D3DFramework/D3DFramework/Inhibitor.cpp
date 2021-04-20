#include "stdafx.h"
#include "Inhibitor.h"
#include "SphereCollider.h"
#include "DeferredStaticMeshRenderer.h"
#include "TurretFloatingBar.h"

Inhibitor::Inhibitor()
{
	transform->position = { 0,0,0 };
	transform->scale = { 0.00018f, 0.00018f, 0.00018f, };

	bar->SetOffset(Vector3(0, 2.5f, 0));

	StaticMesh* mesh = RenderManager::CloneStaticMesh(L"sruap_orderinhibitor");
	AddComponent(L"StaticMesh", mesh);

	collider->SetRadius(1.5f);
	Engine::DeferredStaticMeshRenderer* renderer =
		(Engine::DeferredStaticMeshRenderer*)AddComponent<Engine::DeferredStaticMeshRenderer>(L"renderer");
	renderer->SetMesh(mesh);

	// 스탯
	stat->SetBaseValue(StatType::MaxHealth, 620.f);
	stat->SetBaseValue(StatType::Health, 620.f);
	stat->SetBaseValue(StatType::HealthRegen, 8.f);
}

Inhibitor::~Inhibitor()
{
	bar = nullptr;
}

void Inhibitor::SetTeam(Team _team)
{
	Unit::SetTeam(_team);

	if (_team == Team::BLUE)
	{
		bar->SetTextureHP(L"bar_float (5)");
	}
	else
	{
		bar->SetTextureHP(L"bar_float (2)");
	}
}