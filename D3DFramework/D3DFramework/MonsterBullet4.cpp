#include "stdafx.h"
#include "MonsterBullet4.h"
#include "Player4.h"
#include "Cube.h"
#include "CollisionManager4.h"
#include "Effect4.h"
PKH::MonsterBullet4::MonsterBullet4()
{
	BulletPosZ = 0;
}
PKH::MonsterBullet4::~MonsterBullet4()
{
}
void PKH::MonsterBullet4::Ready()
{
	switch (BulletCode)
	{
	case 1:
		transform->scale = { 0.8f, 0.8f, 0.8f };
		TargetPlayer = ObjectManager::GetInstance()->FindObject<Player4>();
		if (TargetPlayer == nullptr) {
			isDead = true;
			return;
		}
		TargetPos = TargetPlayer->transform->position;
		dir = TargetPos - transform->position;
		Vector3::Normalize(&dir);
		moveSpeed = 4.f;
		break;
	case 2:
		transform->scale = { 0.8f, 0.8f, 0.8f };

		moveSpeed = 4.f;
		break;
	case 3:
		transform->scale = { 1.8f, 1.8f, 1.8f };

		moveSpeed = 4.f;
		break;
	default:
		break;
	}

	Cube* Comp = dynamic_cast<Cube*>(AddComponent<PKH::Cube>(L"Mesh"));
	if (BulletPosZ == 0)
		Comp->SetColor(D3DCOLOR_XRGB(103, 153, 255));
	else if (BulletPosZ == 1)
		Comp->SetColor(D3DCOLOR_XRGB(241, 95, 95));
	else
		Comp->SetColor(D3DCOLOR_XRGB(134, 229, 127));
}

void PKH::MonsterBullet4::Update()
{
	if (transform->position.x < -10 || transform->position.x > 10
		|| transform->position.y < -5 || transform->position.y > 5
		|| transform->position.z < -5 || transform->position.z > 5) {
		isDead = true;
		CollisionManager4::FindObjectDelete(dynamic_cast<GameObject*>(this));
	}

	if (1 == BulletCode) { // 플레이어 유도 총알
		//Move(TargetPos);
		if (TargetPlayer != nullptr)
		{
		transform->position.x += dir.x * moveSpeed * TimeManager::DeltaTime();
		transform->position.y += dir.y * moveSpeed * TimeManager::DeltaTime();
		//transform->position.z += dir.z * moveSpeed * TimeManager::DeltaTime();

		//float rotX = atan2f(dir.z, dir.y);
		//float rotY = atan2f(dir.x, dir.z);
		//float rotZ = atan2f(dir.y, dir.x);

		//if(transform->rotation.x < rotX)
		//transform->rotation.x += rotX * TimeManager::DeltaTime();
		//if (transform->rotation.y < rotY)
		//transform->rotation.y += rotY * TimeManager::DeltaTime();
		//if (transform->rotation.z < rotZ)
		//transform->rotation.z += rotZ * TimeManager::DeltaTime();
		}
	}
	else if (2 == BulletCode) { //방향만 따져서 일자로
		transform->position.x += dir.x * moveSpeed * TimeManager::DeltaTime();
		transform->position.y += dir.y * moveSpeed * TimeManager::DeltaTime();
	}
	else if (3 == BulletCode) { //방향만 따져서 일자로
		transform->position.x += dir.x * moveSpeed * TimeManager::DeltaTime();
	}


	GameObject::Update();
}

void PKH::MonsterBullet4::OnCollision(GameObject* target)
{
	for (int i = 0; i < 4; i++) {
		Effect4* e = (Effect4*)ObjectManager::GetInstance()->CreateObject<Effect4>();
		*(e->GetTransform()->Get_Pos()) = transform->position;
		e->Ready();
	}
	isDead = true;
}