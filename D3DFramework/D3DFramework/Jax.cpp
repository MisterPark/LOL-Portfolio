#include "stdafx.h"
#include "Jax.h"

Jax::Jax()
{
	transform->scale = { 0.016f, 0.016f, 0.016f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"jax");
	AddComponent(L"DynamicMesh", dmesh);

	anim->AttachToDynamicMesh(dmesh);
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
