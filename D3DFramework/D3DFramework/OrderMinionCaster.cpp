#include "stdafx.h"
#include "OrderMinionCaster.h"

OrderMinionCaster::OrderMinionCaster()
{
	transform->scale = { 0.012f, 0.012f, 0.012f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"order_minion_caster");
	AddComponent(L"DynamicMesh", dmesh);

	Engine::SkinnedMeshRenderer* renderer = new Engine::SkinnedMeshRenderer(this);
	renderer->SetMesh(dmesh);
	AddComponent(L"renderer", renderer);

	anim->AttachToDynamicMesh(dmesh);

	stat->SetBaseValue(StatType::Health, 296.f);
	stat->SetBaseValue(StatType::MaxHealth, 296.f);
	stat->SetBaseValue(StatType::AttackDamage, 24.f);
	stat->SetBaseValue(StatType::AttackSpeed, 0.667f);
	stat->SetBaseValue(StatType::MovementSpeed, 3.25f);
	stat->SetBaseValue(StatType::Range, 5.5f);
	stat->SetBaseValue(StatType::Bounty, 14.f);
	stat->SetBaseValue(StatType::MinionKilled, 1.f);

	faceCircleTexkey = L"bluerange_circle";
	faceSquareTexkey = L"bluerange_square";
}

OrderMinionCaster::~OrderMinionCaster()
{
}
