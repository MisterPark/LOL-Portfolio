#include "stdafx.h"
#include "Monster.h"
#include "Player.h"


PKH::Monster::Monster()
{
	transform.position.z = 3;
}

PKH::Monster::~Monster()
{
}

void PKH::Monster::Update()
{
	transform.rotation.x += 5.0f * TimeManager::DeltaTime();
	transform.rotation.z += 5.f * TimeManager::DeltaTime();

	GameObject* player = ObjectManager::GetInstance()->FindObject<Player>();
	if (player != nullptr)
	{
		Vector3 dir = player->transform.position - transform.position;
		Vector3::Normalize(&dir);

		transform.position.x += dir.x * TimeManager::DeltaTime();
		transform.position.y += dir.y * TimeManager::DeltaTime();
		transform.position.z += dir.z * TimeManager::DeltaTime();
	}
	

	for (auto& comp : components)
	{
		comp.second->Update();
	}
}

void PKH::Monster::Render()
{
	for (auto& comp : components)
	{
		Mesh* mesh = dynamic_cast<Mesh*>(comp.second);
		if (mesh == nullptr) continue;

		mesh->Render();
	}
}
