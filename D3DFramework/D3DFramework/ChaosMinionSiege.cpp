#include "stdafx.h"
#include "ChaosMinionSiege.h"

ChaosMinionSiege::ChaosMinionSiege()
{
	transform->scale = { 0.015f, 0.015f, 0.015f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"chaos_minion_siege");
	AddComponent(L"DynamicMesh", dmesh);

	Engine::SkinnedMeshRenderer* renderer = new Engine::SkinnedMeshRenderer(this);
	renderer->SetMesh(dmesh);
	AddComponent(L"renderer", renderer);

	anim->AttachToDynamicMesh(dmesh);

	stat->SetBaseValue(StatType::Health, 900.f);
	stat->SetBaseValue(StatType::MaxHealth, 900.f);
	stat->SetBaseValue(StatType::AttackDamage, 41.f);
	stat->SetBaseValue(StatType::AttackSpeed, 0.667f);
	stat->SetBaseValue(StatType::MovementSpeed, 3.25f);
	stat->SetBaseValue(StatType::Range, 3.f);
	stat->SetBaseValue(StatType::Bounty, 60.f);
	stat->SetBaseValue(StatType::MinionKilled, 1.f);

	faceCircleTexkey = L"redmechcannon_circle";
	faceSquareTexkey = L"redmechcannon_square";
}

ChaosMinionSiege::~ChaosMinionSiege()
{
}
