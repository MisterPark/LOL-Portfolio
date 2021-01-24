#include "stdafx.h"
#include "Leesin.h"

Leesin::Leesin()
{
	transform->scale = { 0.018f, 0.018f, 0.018f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"leesin");
	AddComponent(L"DynamicMesh", dmesh);

	anim->AttachToDynamicMesh(dmesh);
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
		transform->position.z -= movementSpeed * dt;
	}
	if (InputManager::GetKey(VK_DOWN))
	{
		transform->position.z += movementSpeed * dt;
	}
	if (InputManager::GetKey(VK_LEFT))
	{
		transform->position.x += movementSpeed * dt;
	}
	if (InputManager::GetKey(VK_RIGHT))
	{
		transform->position.x -= movementSpeed * dt;
	}
	Champion::Update();
}
