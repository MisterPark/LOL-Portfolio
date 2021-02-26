#include "stdafx.h"
#include "Jax.h"
#include "SkinnedMeshRenderer.h"
Jax::Jax()
{
	transform->scale = { 0.016f, 0.016f, 0.016f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"jax");
	AddComponent(L"DynamicMesh", dmesh);
	anim->AttachToDynamicMesh(dmesh);

	Engine::SkinnedMeshRenderer* renderer = new Engine::SkinnedMeshRenderer(this);
	renderer->SetMesh(dmesh);
	AddComponent(L"renderer", renderer);

	faceCircleTexkey = L"jax_circle";
	faceSquareTexkey = L"jax_square";
	// 스킬 아이콘
	qTexKey = L"jax_q";
	wTexKey = L"jax_w";
	eTexKey = L"jax_e";
	rTexKey = L"jax_r";
	passiveTexKey = L"jax_passive";

	SetHP(592.8f);
	SetHPRegen(8.5f);
	SetMP(338.8f);
	SetMPRegen(7.5f);
	SetAttackDamage(68.f);
	SetAttackPerSec(0.638f);
	SetArmor(36.f);
	SetMagicResistance(31.25f);
	SetAttackRange(1.25f);
	SetMovementSpeed(3.5f);
}

Jax::~Jax()
{
}

void Jax::Initialize()
{
}

void Jax::Release()
{
}

void Jax::Update()
{
	Champion::Update();
}
