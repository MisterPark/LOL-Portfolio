#include "stdafx.h"
#include "Leesin.h"

Leesin::Leesin()
{
	transform->scale = { 0.018f, 0.018f, 0.018f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"leesin");
	AddComponent(L"DynamicMesh", dmesh);
	anim->AttachToDynamicMesh(dmesh);

	Engine::SkinnedMeshRenderer* renderer = new Engine::SkinnedMeshRenderer(this);
	renderer->SetMesh(dmesh);
	AddComponent(L"renderer", renderer);

	faceCircleTexkey = L"leesin_circle";
	faceSquareTexkey = L"leesin_square";
	// 스킬 아이콘
	qTexKey = L"leesin_q";
	wTexKey = L"leesin_w";
	eTexKey = L"leesin_e";
	rTexKey = L"leesin_r";
	passiveTexKey = L"leesin_passive";

	stat->SetBaseValue(StatType::MaxHealth, 575.f);
	stat->SetBaseValue(StatType::Health, 575.f);
	stat->SetBaseValue(StatType::HealthRegen, 7.5f);
	stat->SetBaseValue(StatType::MaxMana, 200.f);
	stat->SetBaseValue(StatType::Mana, 200.f);
	stat->SetBaseValue(StatType::ManaRegen, 50.f);
	stat->SetBaseValue(StatType::AttackDamage, 70.f);
	stat->SetBaseValue(StatType::AttackSpeed, 0.651f);
	stat->SetBaseValue(StatType::Armor, 36.f);
	stat->SetBaseValue(StatType::MagicResistance, 32.1f);
	stat->SetBaseValue(StatType::Range, 1.25f);
	stat->SetBaseValue(StatType::MovementSpeed, 3.45f);
}

Leesin::~Leesin()
{
}

void Leesin::Initialize()
{
}

void Leesin::Release()
{
}