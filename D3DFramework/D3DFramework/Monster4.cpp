#include "stdafx.h"
#include "Monster4.h"
#include "Player4.h"
#include "MonsterBullet4.h"
#include "Cube.h"
#include "Monster.h"
#include "CollisionManager4.h"
#include "Random_Manager4.h"
#include "Effect4.h"

PKH::Monster4::Monster4()
{
	TargetPlayer = nullptr;
	MonsterCode = 0;
	MonsterBulletRegenTime = 0.f;
	MonsterPatternTime = 0.f;
	MonsterPosZ = 0;
	MonsterHp = 4;
}

PKH::Monster4::~Monster4()
{
}

void PKH::Monster4::Ready()
{
	transform->position.z = (float)MonsterPosZ * 0.5f;

	switch (MonsterCode)
	{
	case 1:
		transform->scale = { 3.f, 3.f, 3.f };
		transform->position.x = 4.f;
		TargetPlayer = ObjectManager::GetInstance()->FindObject<Player4>();
		if (TargetPlayer == nullptr) {
			isDead = true;
			return;
		}
		TargetPos = TargetPlayer->transform->position;
		dir = TargetPos - transform->position;
		Vector3::Normalize(&dir);
		moveSpeed = 1.5f;
		break;
	case 2:
		transform->scale = { 2.f ,2.f, 2.f };
		transform->position.x = 3.f;
		transform->position.y = -3.f;
		moveSpeed = 7.5f;
		MonsterPatternTime = 0.f;
		break;
	case 3:
		transform->scale = { 3.f, 3.f, 3.f };
		transform->position.x = 4.f;
		transform->position.y = -3.f + (Random_Manager::Random4() % 60 * 0.1f);
		moveSpeed = 1.5f;
		break;
	default:
		break;
	}
}


void PKH::Monster4::Update()
{
	if (transform->position.x < -5 || transform->position.x > 5
		|| transform->position.y < -5 || transform->position.y > 5){
		CollisionManager4::FindObjectDelete(dynamic_cast<GameObject*>(this));
		isDead = true;
	}

	MonsterPattern();

	GameObject::Update();
}


void PKH::Monster4::MonsterPattern() {
	if (1 == MonsterCode) {
		if (TargetPlayer != nullptr)
		{
			//Move(TargetPos);

			transform->position.x += dir.x * moveSpeed * TimeManager::DeltaTime();
			transform->position.y += dir.y * moveSpeed * TimeManager::DeltaTime();
			//transform->position.z = 0.f;

			//float rotX = atan2f(dir.z, dir.y);
			//float rotY = atan2f(dir.x, dir.z);
			//float rotZ = atan2f(dir.y, dir.x);

			//if(transform->rotation.x < rotX)
			//transform->rotation.x += rotX * TimeManager::DeltaTime();
			//if (transform->rotation.y < rotY)
			//transform->rotation.y += rotY * TimeManager::DeltaTime();
			//if (transform->rotation.z < rotZ)
			//transform->rotation.z += rotZ * TimeManager::DeltaTime();

			MonsterBulletRegenTime += TimeManager::DeltaTime();
			if (MonsterBulletRegenTime > 1.f) {
				MonsterBulletRegenTime = 0.f;
				CreateBullet(1);
			}
		}
	}
	else if (2 == MonsterCode) {
		MonsterPatternTime += TimeManager::DeltaTime();
		if (MonsterPatternTime > 1.f) {
			MonsterBulletRegenTime += TimeManager::DeltaTime();
			if (transform->position.y > -3.f &&  MonsterBulletRegenTime > 0.3f) {
				MonsterBulletRegenTime = 0.f;
				CreateBullet(1);
			}
			transform->position.y -= moveSpeed * TimeManager::DeltaTime();
			if (moveSpeed < 8.f)
				moveSpeed *= 1.05f;
		}
		else {
			if (moveSpeed > 0.5f)
				moveSpeed *= 0.95f;
			transform->position.y += moveSpeed * TimeManager::DeltaTime();
		}
	}
	else if (3 == MonsterCode) {		
		transform->position.x -= moveSpeed * TimeManager::DeltaTime();

		MonsterBulletRegenTime += TimeManager::DeltaTime();
		if (MonsterBulletRegenTime > 1.f) {
			MonsterBulletRegenTime = 0.f;
			CreateBullet(1);
		}
	}
}

void PKH::Monster4::CreateBullet(int Code) {
	MonsterBullet4* b = (MonsterBullet4*)ObjectManager::GetInstance()->CreateObject<MonsterBullet4>();
	CollisionManager4::GetInstance()->RegisterObject(CollisionManager4::MONSTER_BULLET, b);
	b->SetPosZ(MonsterPosZ);
	b->transform->position.z = (float)MonsterPosZ;
	b->SetCode(Code);
	*(b->GetTransform()->Get_Pos()) = transform->position;
	b->Ready();
}

void PKH::Monster4::OnCollision(GameObject* target)
{
	for (int i = 0; i < 6; i++)
	{
		Effect4* e = (Effect4*)ObjectManager::GetInstance()->CreateObject<Effect4>();
		*(e->GetTransform()->Get_Pos()) = transform->position;
		e->Ready();
	}
	
	isDead = true;
}