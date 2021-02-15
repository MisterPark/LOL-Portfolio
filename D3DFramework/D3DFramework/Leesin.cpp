#include "stdafx.h"
#include "Leesin.h"

Leesin::Leesin()
{
	transform->scale = { 0.018f, 0.018f, 0.018f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"leesin");
	AddComponent(L"DynamicMesh", dmesh);
	anim->AttachToDynamicMesh(dmesh);

	faceCircleTexkey = L"leesin_circle";
	faceSquareTexkey = L"leesin_square";
	// 스킬 아이콘
	qTexKey = L"leesin_q";
	wTexKey = L"leesin_w";
	eTexKey = L"leesin_e";
	rTexKey = L"leesin_r";
	passiveTexKey = L"leesin_passive";

	SetHP(575.f);
	SetHPRegen(7.5f);
	SetMP(200.f);
	SetMPRegen(50.f);
	SetAttackDamage(70.f);
	SetAttackPerSec(0.651f);
	SetArmor(36.f);
	SetMagicResistance(32.1f);
	SetAttackRange(1.25f);
	SetMovementSpeed(3.45f);
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

void Leesin::Update()
{
	float dt = TimeManager::DeltaTime();

	if (InputManager::GetKey(VK_UP))
	{
		transform->position.z -= stat->movementSpeed.GetValue() * dt;
	}
	if (InputManager::GetKey(VK_DOWN))
	{
		transform->position.z += stat->movementSpeed.GetValue() * dt;
	}
	if (InputManager::GetKey(VK_LEFT))
	{
		transform->position.x += stat->movementSpeed.GetValue() * dt;
	}
	if (InputManager::GetKey(VK_RIGHT))
	{
		transform->position.x -= stat->movementSpeed.GetValue() * dt;
	}
	Champion::Update();
}
