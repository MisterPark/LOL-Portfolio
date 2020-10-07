#include "stdafx.h"
#include "Monster.h"
#include "Player.h"


PKH::Monster::Monster()
{
	transform->scale = { 3,3,3 };
}

PKH::Monster::~Monster()
{
}

void PKH::Monster::Update()
{
	
	GameObject* player = ObjectManager::GetInstance()->FindObject<Player>();
	if (player != nullptr)
	{
		Vector3 dir = player->transform->position - transform->position;
		Vector3::Normalize(&dir);

		Move(player->transform->position);


		float rotX = atan2f(dir.z, dir.y) + D3DXToRadian(180.f);
		float rotY = atan2f(dir.x, dir.z) + D3DXToRadian(180.f);
		float rotZ = atan2f(dir.y, dir.x) + D3DXToRadian(180.f);

		transform->rotation.x = rotX;
		transform->rotation.y = rotY;
		transform->rotation.z = rotZ;
		

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
