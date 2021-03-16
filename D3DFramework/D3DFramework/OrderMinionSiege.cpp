#include "stdafx.h"
#include "OrderMinionSiege.h"

OrderMinionSiege::OrderMinionSiege()
{
	transform->scale = { 0.014f, 0.014f, 0.014f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"order_minion_siege");
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
	stat->SetBaseValue(StatType::Gold, 60.f);
}

OrderMinionSiege::~OrderMinionSiege()
{
}
