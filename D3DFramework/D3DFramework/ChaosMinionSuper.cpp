#include "stdafx.h"
#include "ChaosMinionSuper.h"

ChaosMinionSuper::ChaosMinionSuper()
{
	transform->scale = { 0.014f, 0.014f, 0.014f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"chaos_minion_super");
	AddComponent(L"DynamicMesh", dmesh);

	Engine::SkinnedMeshRenderer* renderer = new Engine::SkinnedMeshRenderer(this);
	renderer->SetMesh(dmesh);
	AddComponent(L"renderer", renderer);

	anim->AttachToDynamicMesh(dmesh);

	stat->SetBaseValue(StatType::Health, 1600.f);
	stat->SetBaseValue(StatType::MaxHealth, 1600.f);
	stat->SetBaseValue(StatType::AttackDamage, 230.f);
	stat->SetBaseValue(StatType::AttackSpeed, 0.85f);
	stat->SetBaseValue(StatType::Armor, 100.f);
	stat->SetBaseValue(StatType::MagicResistance, -30.f);
	stat->SetBaseValue(StatType::MovementSpeed, 3.25f);
	stat->SetBaseValue(StatType::Range, 1.7f);
	stat->SetBaseValue(StatType::Bounty, 60.f);
	stat->SetBaseValue(StatType::MinionKilled, 1.f);
}

ChaosMinionSuper::~ChaosMinionSuper()
{
}
