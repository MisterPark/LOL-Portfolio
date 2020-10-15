#include "stdafx.h"
#include "Boss4.h"
#include "Player4.h"
#include "Cube.h"
#include "Random_Manager4.h"
#include "ObjectManager.h"
#include "MonsterBullet4.h"
#include "CollisionManager4.h"
#include "Effect4.h"


PKH::Boss4::Boss4()
{
	TargetPlayer = nullptr;
	BossBulletRegenTime = 0.f;
	for (int i = 0; i < 3; i++)
	{
		BossPatternTime[i] = 0.f;
	}
	BossHp = 50;
	Cube* Comp = dynamic_cast<Cube*>(AddComponent<PKH::Cube>(L"Mesh"));
	Comp->SetColor(D3DCOLOR_XRGB(103, 153, 255));
	BossPatternNumber1 = 0;
	BossPatternNumber2 = 0;

}

PKH::Boss4::~Boss4()
{
}

void PKH::Boss4::Ready()
{
	transform->scale = { 5.f, 5.f, 5.f };
	transform->position.x = 4.f;
	transform->position.y = 0.7f;
	TargetPlayer = ObjectManager::GetInstance()->FindObject<Player4>();
	if (TargetPlayer == nullptr) {
		isDead = true;
		return;
	}
	TargetPos = TargetPlayer->transform->position;
	dir = TargetPos - transform->position;
	Vector3::Normalize(&dir);
	moveSpeed = 0.5f;
}

void PKH::Boss4::Update()
{
	BossPattern();
	
	GameObject::Update();
}

void PKH::Boss4::BossPattern() {
	
	if (BossPatternTime[0] <= 1.5f) {
		BossPatternTime[0] += TimeManager::DeltaTime();
		transform->position.x -= moveSpeed * 2.f * TimeManager::DeltaTime();
	}
	else {
		BossPatternTime[1] += TimeManager::DeltaTime();
		if (BossPatternTime[1] <= 3.f) {
			transform->position.y -= moveSpeed * TimeManager::DeltaTime();
		}
		else {
			transform->position.y += moveSpeed * TimeManager::DeltaTime();
		}
		if (BossPatternTime[1] >= 6.f)
			BossPatternTime[1] = 0.f;
	}

	if (BossPatternNumber1 == 0) {
		BossPatternTime[2] += TimeManager::DeltaTime();
		if (BossPatternTime[2] >= 2) {
			BossPatternTime[2] = 0.f;
			BossPatternNumber1 = (Random_Manager::Random4() % 3) + 1;
			//BossPatternNumber1 = 3;
		}
	}
	else if (BossPatternNumber1 == 1) {
		BossPatternTime[2] += TimeManager::DeltaTime();
		BossPatternTime[3] += TimeManager::DeltaTime();
		if (BossPatternTime[2] < 2.f) {
			if (BossPatternTime[3] >= 0.05f) {
				CreateBullet2(Vector3{ -0.3f + (0.1f * (Random_Manager::Random4() % 7)), 1.f,0.f }, Random_Manager::Random4() % 3);
				BossPatternTime[3] = 0.f;
			}
		}
		else if (BossPatternTime[2] > 3.f && BossPatternTime[2] < 6.f) {
			if (BossPatternTime[3] >= 0.7f) {
				for (int i = 0; i < 8; i++)
				{
					int RandomZ = Random_Manager::Random4() % 3;
					CreateBullet3(2, Vector3{ -0.7f, -0.7f, 0.f }, RandomZ, Vector3{ -0.6f + (i * 1.2f) + (RandomZ * 0.1f), 4.f + (0.2f * RandomZ), RandomZ * 0.5f });
				}
				BossPatternTime[3] = 0.f;
			}
		}
		if (BossPatternTime[2] > 8.f) {
			BossPatternNumber1 = 0;
			BossPatternTime[2] = 0.f;
			BossPatternTime[3] = 0.f;
		}
	}
	else if (BossPatternNumber1 == 2) {
		BossPatternTime[2] += TimeManager::DeltaTime();
		BossPatternTime[3] += TimeManager::DeltaTime();
		if (BossPatternTime[2] < 2.f) {
			if (BossPatternTime[3] >= 0.05f) {
				CreateBullet2(Vector3{ -0.3f + (0.1f * (Random_Manager::Random4() % 7)), 1.f,0.f }, Random_Manager::Random4() % 2 + 1);
				BossPatternTime[3] = 0.f;
			}
		}
		else if (BossPatternTime[2] > 3.5f && BossPatternTime[2] < 5.f) {
			if (BossPatternTime[3] >= 0.2f) {
				for (int i = 0; i < 16; i++)
				{
					int RandomZ = Random_Manager::Random4() % 2 + 1;
					CreateBullet3(2, Vector3{ -0.7f, -0.7f, 0.f }, RandomZ, Vector3{ 0.f + (0.5f * i), 4.f + (0.2f * RandomZ), RandomZ * 0.5f });
				}
				BossPatternTime[3] = 0.f;
			}
		}

		if (BossPatternTime[2] > 8.f) {
			BossPatternNumber1 = 0;
			BossPatternTime[2] = 0.f;
			BossPatternTime[3] = 0.f;
		}
	}
	else if (BossPatternNumber1 == 2) {
		BossPatternTime[2] += TimeManager::DeltaTime();
		BossPatternTime[3] += TimeManager::DeltaTime();
		if (BossPatternTime[2] < 2.f) {
			if (BossPatternTime[3] >= 0.05f) {
				CreateBullet2(Vector3{ -0.3f + (0.1f * (Random_Manager::Random4() % 7)), 1.f,0.f }, Random_Manager::Random4() % 2 + 1);
				BossPatternTime[3] = 0.f;
			}
		}
		else if (BossPatternTime[2] > 3.5f && BossPatternTime[2] < 5.f) {
			if (BossPatternTime[3] >= 0.2f) {
				for (int i = 0; i < 16; i++)
				{
					int RandomZ = Random_Manager::Random4() % 2 + 1;
					CreateBullet3(2, Vector3{ -0.7f, -0.7f, 0.f }, RandomZ, Vector3{ 0.f + (0.5f * i), 4.f + (0.2f * RandomZ), RandomZ * 0.5f });
				}
				BossPatternTime[3] = 0.f;
			}
		}

		if (BossPatternTime[2] > 8.f) {
			BossPatternNumber1 = 0;
			BossPatternTime[2] = 0.f;
			BossPatternTime[3] = 0.f;
		}
	}
	else if (BossPatternNumber1 == 3) {
		BossPatternTime[2] += TimeManager::DeltaTime();
		BossPatternTime[3] += TimeManager::DeltaTime();

		if (BossPatternTime[2] > 2.f && BossPatternTime[2] < 5.f) {
			if (BossPatternTime[3] >= 0.2f) {
				switch (BossPatternNumber2) //12
				{
				case 0:
					for (int i = 0; i < 6; i++)
					{
						CreateBullet3(3, Vector3{ -1.f, 0.f, 0.f }, 0, Vector3{ 4.f, 3.f - 0.5f * i, 0 });
					}
					for (int i = 0; i < 3; i++)
					{
						CreateBullet3(3, Vector3{ -1.f, 0.f, 0.f }, 2, Vector3{ 4.f, 0.f - 0.5f * i, 2 });
					}
					for (int i = 0; i < 3; i++)
					{
						CreateBullet3(3, Vector3{ -1.f, 0.f, 0.f }, 0, Vector3{ 4.f, -1.5f - 0.5f * i, 0 });
					}
					break;
				case 1:
					for (int i = 0; i < 5; i++)
					{
						CreateBullet3(3, Vector3{ -1.f, 0.f, 0.f }, 0, Vector3{ 4.f, 3.f - 0.5f * i, 0 });
					}
					for (int i = 0; i < 3; i++)
					{
						CreateBullet3(3, Vector3{ -1.f, 0.f, 0.f }, 2, Vector3{ 4.f, 0.5f - 0.5f * i, 2 });
					}
					for (int i = 0; i < 4; i++)
					{
						CreateBullet3(3, Vector3{ -1.f, 0.f, 0.f }, 0, Vector3{ 4.f, -1.f - 0.5f * i, 0 });
					}
					break;
				case 2:
					for (int i = 0; i < 4; i++)
					{
						CreateBullet3(3, Vector3{ -1.f, 0.f, 0.f }, 0, Vector3{ 4.f, 3.f - 0.5f * i, 0 });
					}
					for (int i = 0; i < 3; i++)
					{
						CreateBullet3(3, Vector3{ -1.f, 0.f, 0.f }, 2, Vector3{ 4.f, 1.f - 0.5f * i, 2 });
					}
					for (int i = 0; i < 5; i++)
					{
						CreateBullet3(3, Vector3{ -1.f, 0.f, 0.f }, 0, Vector3{ 4.f, -0.5f - 0.5f * i, 0 });
					}
					break;
				case 3:
					for (int i = 0; i < 5; i++)
					{
						CreateBullet3(3, Vector3{ -1.f, 0.f, 0.f }, 0, Vector3{ 4.f, 3.f - 0.5f * i, 0 });
					}
					for (int i = 0; i < 3; i++)
					{
						CreateBullet3(3, Vector3{ -1.f, 0.f, 0.f }, 2, Vector3{ 4.f, 0.5f - 0.5f * i, 2 });
					}
					for (int i = 0; i < 4; i++)
					{
						CreateBullet3(3, Vector3{ -1.f, 0.f, 0.f }, 0, Vector3{ 4.f, -1.f - 0.5f * i, 0 });
					}
					break;
				case 4:
					for (int i = 0; i < 6; i++)
					{
						CreateBullet3(3, Vector3{ -1.f, 0.f, 0.f }, 0, Vector3{ 4.f, 3.f - 0.5f * i, 0 });
					}
					for (int i = 0; i < 3; i++)
					{
						CreateBullet3(3, Vector3{ -1.f, 0.f, 0.f }, 2, Vector3{ 4.f, 0.f - 0.5f * i, 2 });
					}
					for (int i = 0; i < 3; i++)
					{
						CreateBullet3(3, Vector3{ -1.f, 0.f, 0.f }, 0, Vector3{ 4.f, -1.5f - 0.5f * i, 0 });
					}
					break;
				default:
					break;
				}
				if (BossPatternNumber2 != 4)
					BossPatternNumber2++;
				else
					BossPatternNumber2 = 0;
				BossPatternTime[3] = 0.f;
			}
		}
		if (BossPatternTime[2] > 8.f) {
			BossPatternNumber1 = 0;
			BossPatternTime[2] = 0.f;
			BossPatternTime[3] = 0.f;
		}
	}
}

void PKH::Boss4::CreateBullet2(Vector3 _vec, int BulletPosZ) {
	MonsterBullet4* b = (MonsterBullet4*)ObjectManager::GetInstance()->CreateObject<MonsterBullet4>();
	CollisionManager4::GetInstance()->RegisterObject(CollisionManager4::MONSTER_BULLET, b);
	b->SetPosZ(BulletPosZ);
	b->SetDir(_vec);
	b->transform->position.z = (float)BulletPosZ;
	b->SetCode(2);
	*(b->GetTransform()->Get_Pos()) = transform->position;
	b->Ready();
}

void PKH::Boss4::CreateBullet3(int Code, Vector3 _vec, int BulletPosZ, Vector3 _pos) {
	MonsterBullet4* b = (MonsterBullet4*)ObjectManager::GetInstance()->CreateObject<MonsterBullet4>();
	CollisionManager4::GetInstance()->RegisterObject(CollisionManager4::MONSTER_BULLET, b);
	b->SetPosZ(BulletPosZ);
	b->SetDir(_vec);
	b->transform->position.z = (float)BulletPosZ;
	b->SetCode(Code);
	*(b->GetTransform()->Get_Pos()) = _pos;
	b->Ready();
}

void PKH::Boss4::OnCollision(GameObject* target)
{
	for (int i = 0; i < 10; i++)
	{
		Effect4* e = (Effect4*)ObjectManager::GetInstance()->CreateObject<Effect4>();
		*(e->GetTransform()->Get_Pos()) = transform->position;
		e->Ready();
	}
	dynamic_cast<Player4*>(ObjectManager::GetInstance()->FindObject<Player4>())->SetBossDie();
	isDead = true;
}