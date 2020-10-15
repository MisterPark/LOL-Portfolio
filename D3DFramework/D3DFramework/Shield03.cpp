#include "stdafx.h"
#include "Shield03.h"
#include "Player03.h"
#include "Monster03.h"
#include "Cube.h"
#include "Bullet03.h"
#include "Effect03.h"
PKH::Shield03::Shield03()
{
	transform->scale = { 1.f,1.f,1.f };
	moveSpeed = 10.f;
}



PKH::Shield03::~Shield03()
{
}

void PKH::Shield03::Update()
{
	GameObject* player = ObjectManager::GetInstance()->FindObject<Player03>();
	Player03* p = dynamic_cast<Player03*>(player);
	if (!isSetting)
	{
		Mesh* mesh = (Mesh*)AddComponent<PKH::Cube>(L"Mesh");
		mesh->SetColor(D3DCOLOR_RGBA(0, p->MyColor, p->MyColor, p->MyColor));
		
		isSetting = true;
		
	}
	
	transform->scale += Vector3{ 0.2f,0.2f,0.f };
	
	GameObject* bullet = ObjectManager::GetInstance()->FindObject<Bullet03>();
	if (bullet != nullptr)
	{
		float fRadiusSum = static_cast<float>((bullet->transform->scale.z) + (transform->scale.z));
		float fX = bullet->transform->position.x - transform->position.x;
		float fY = bullet->transform->position.y - transform->position.y;
		float fZ = bullet->transform->position.z - transform->position.z;
		float fDist = sqrtf(fX * fX + fY * fY + fZ * fZ);

		if (fDist - fRadiusSum < 0)
		{

			for (int i = 0; i < 4; i++)
			{
				Effect03* e = (Effect03*)ObjectManager::GetInstance()->CreateObject<Effect03>();
				e->SetPosition(bullet->transform->position);
				e->PlayerHit = true;
				e->effectDir = i;
				dynamic_cast<Bullet03*>(bullet)->Die();
			}


			
			
		}

	}
	DieTime += 4.f * TimeManager::DeltaTime();
	if (DieTime > 6)
	{
		Die();
	}
	GameObject::Update();
}

