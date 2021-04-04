#include "stdafx.h"
#include "OrderMinionMelee.h"

OrderMinionMelee::OrderMinionMelee()
{
	transform->scale = { 0.012f, 0.012f, 0.012f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"order_minion_melee");
	AddComponent(L"DynamicMesh", dmesh);

	Engine::SkinnedMeshRenderer* renderer = new Engine::SkinnedMeshRenderer(this);
	renderer->SetMesh(dmesh);
	AddComponent(L"renderer", renderer);

	anim->AttachToDynamicMesh(dmesh);

	stat->SetBaseValue(StatType::Health, 477.f);
	stat->SetBaseValue(StatType::MaxHealth, 477.f);
	stat->SetBaseValue(StatType::AttackDamage, 12.f);
	stat->SetBaseValue(StatType::AttackSpeed, 1.25f);
	stat->SetBaseValue(StatType::MovementSpeed, 3.25f);
	stat->SetBaseValue(StatType::Range, 1.1f);
	stat->SetBaseValue(StatType::Gold, 21.f);


}

OrderMinionMelee::~OrderMinionMelee()
{
}
