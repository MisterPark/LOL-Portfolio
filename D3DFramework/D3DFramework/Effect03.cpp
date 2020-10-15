#include "stdafx.h"
#include "Effect03.h"
#include "Player03.h"
#include "Monster03.h"
#include "Cube.h"

PKH::Effect03::Effect03()
{
	
	transform->scale = { 1.f,1.f,1.f };
	moveSpeed = 10.f;
}



PKH::Effect03::~Effect03()
{
}

void PKH::Effect03::Update()
{

	if (PlayerHit)
	{

		GameObject* player = ObjectManager::GetInstance()->FindObject<Player03>();
		if (nullptr != player)
		{
			if (!isSetting)
			{
				int color = dynamic_cast<Player03*>(player)->MyColor;
				Mesh* mesh = (Mesh*)AddComponent<PKH::Cube>(L"Mesh");
				mesh->SetColor(D3DCOLOR_XRGB(0, color, color));
				isSetting = true;
			}

		}
	}
	if (!PlayerHit)
	{

		GameObject* monster = ObjectManager::GetInstance()->FindObject<Monster03>();
		if (nullptr != monster)
		{
			if (!isSetting)
			{
				Monster03* mon = dynamic_cast<Monster03*>(monster);
				if (mon->BossType == true)
				{
					int color = mon->MyColor;
					Mesh* mesh = (Mesh*)AddComponent<PKH::Cube>(L"Mesh");
					mesh->SetColor(D3DCOLOR_XRGB(255, color, color));
				}
				if (mon->BossType != true)
				{
					if (mon->xType == true)
					{
						Mesh* mesh = (Mesh*)AddComponent<PKH::Cube>(L"Mesh");
						mesh->SetColor(D3DCOLOR_XRGB(mon->xTypeColor[0], mon->xTypeColor[1], mon->xTypeColor[2]));
					}
					if (mon->yType == true)
					{
						Mesh* mesh = (Mesh*)AddComponent<PKH::Cube>(L"Mesh");
						mesh->SetColor(D3DCOLOR_XRGB(mon->yTypeColor[0], mon->yTypeColor[1], mon->yTypeColor[2]));
					}
					if (mon->xType == false && mon->yType == false)
					{
						Mesh* mesh = (Mesh*)AddComponent<PKH::Cube>(L"Mesh");
						mesh->SetColor(D3DCOLOR_XRGB(mon->zTypeColor[0], mon->zTypeColor[1], mon->zTypeColor[2]));
					}

				}
				isSetting = true;
			}
		}
	}
	transform->scale -= Vector3{ 0.01f,0.01f,0.01f };
	if (effectDir == 0)
	{
		transform->position -= Vector3{0.01f,0.01f, 0.01f };
	}
	if (effectDir == 1)
	{
		transform->position -= Vector3{ -0.01f,0.01f, 0.01f };
	}
	if (effectDir == 2)
	{
		transform->position -= Vector3{ 0.01f,-0.01f, 0.01f };
	}
	if (effectDir == 3)
	{
		transform->position -= Vector3{ -0.01f,-0.01f, 0.01f };
	}
	tick += TimeManager::DeltaTime();
	if (tick > delay)
	{
		Die();
	}


	
	GameObject::Update();
}

