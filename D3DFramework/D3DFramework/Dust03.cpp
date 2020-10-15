#include "stdafx.h"
#include "Dust03.h"
#include "Player03.h"
#include "Monster03.h"
#include "Triangle.h"
PKH::Dust03::Dust03()
{
	transform->scale = { 1.f,1.f,1.f };
	moveSpeed = 10.f;
}



PKH::Dust03::~Dust03()
{
}

void PKH::Dust03::Update()
{

	if(!isSetting)
	{
		Mesh* mesh = (Mesh*)AddComponent<PKH::Triangle>(L"Mesh");
		mesh->SetColor(D3DCOLOR_RGBA(255, 102, 0, 0));
		isSetting = true;
	}
	GameObject* player = ObjectManager::GetInstance()->FindObject<Player03>();
	if (player != nullptr)
	{
		transform->position.z -= moveSpeed * 0.01f;

		if (transform->position.z < 1.f)
			Die();
	}
	DieTime += TimeManager::DeltaTime();
	if (DieTime > 5)
	{
		Die();
	}
	GameObject::Update();
}

