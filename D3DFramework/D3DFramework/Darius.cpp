#include "stdafx.h"
#include "Darius.h"
using namespace Engine;

Darius::Darius()
{
	transform->scale = { 0.014f, 0.014f, 0.014f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"darius");
	AddComponent(L"DynamicMesh", dmesh);
	anim->AttachToDynamicMesh(dmesh);

	Engine::SkinnedMeshRenderer* renderer = new Engine::SkinnedMeshRenderer(this);
	renderer->SetMesh(dmesh);
	AddComponent(L"renderer", renderer);

	anim->SetLoop((int)State::IDLE1, true);

	faceCircleTexkey = L"darius_circle";
	faceSquareTexkey = L"darius_square";
	// 스킬 아이콘
	qTexKey = L"darius_q";
	wTexKey = L"darius_w";
	eTexKey = L"darius_e";
	rTexKey = L"darius_r";
	passiveTexKey = L"darius_passive";

	stat->SetBaseValue(StatType::MaxHealth, 582.f);
	stat->SetBaseValue(StatType::Health, 582.f);
	stat->SetBaseValue(StatType::HealthRegen, 10.f);
	stat->SetBaseValue(StatType::MaxMana, 263.f);
	stat->SetBaseValue(StatType::Mana, 263.f);
	stat->SetBaseValue(StatType::ManaRegen, 6.6f);
	stat->SetBaseValue(StatType::AttackDamage, 64.f);
	stat->SetBaseValue(StatType::AttackSpeed, 0.625f);
	stat->SetBaseValue(StatType::Armor, 39.f);
	stat->SetBaseValue(StatType::MagicResistance, 32.1f);
	stat->SetBaseValue(StatType::Range, 1.75f);
	stat->SetBaseValue(StatType::MovementSpeed, 3.4f);
}

Darius::~Darius()
{
}

void Darius::Initialize()
{
}

void Darius::Release()
{
}

void Darius::Update()
{
	Champion::Update();
}
