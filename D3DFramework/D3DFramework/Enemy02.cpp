#include "stdafx.h"
#include "Enemy02.h"
#include "Bullet02.h"
#include "Cube02.h"
#include "MyCollisionManager.h"

Enemy02::Enemy02()
{
}

Enemy02::Enemy02(Vector3 pos, Vector3 look, int type, GameObject* target) :
	type(type), target(target)
{
	transform->position = pos;
	transform->look = look;

	moveSpeed = 1.f;

	Ready();
}

Enemy02::~Enemy02()
{
}

void Enemy02::Ready()
{
	D3DCOLOR color;
	if (1 == type) color = D3DCOLOR_XRGB(0, 120, 0);
	else color = D3DCOLOR_XRGB(0, 146, 255);

	IComponent* mesh = new Cube02(color);
	mesh->gameObject = this;
	components.emplace(L"Mesh", mesh);
}

void Enemy02::Update()
{
	if (1 == type)
	{
		Pattern01();
	}
	else if (2 == type)
	{
		if (transform->position.z > 0.f)
		{
			Pattern02();
		}
		else Pattern03();
	}
}

void Enemy02::Pattern01()
{
	if (canAttack) Pattern01Bullet();
	else
	{
		coolTime -= TimeManager::DeltaTime();

		if (0.f > coolTime) canAttack = true;
	}

	MoveToTarget(transform->position + transform->look);
}

void Enemy02::Pattern02()
{
	MoveToTarget(transform->position + Vector3::BACK);

	if (canAttack) Pattern02Bullet();
	else
	{
		coolTime -= TimeManager::DeltaTime();

		if (0.f > coolTime) canAttack = true;
	}
}

void Enemy02::Pattern03()
{
	if (!isChange)
	{
		transform->position.z = 0.f;

		isChange = true;
	}

	if (canAttack) Pattern03Bullet();
	else
	{
		coolTime -= TimeManager::DeltaTime();

		if (0.f > coolTime) canAttack = true;
	}
}

void Enemy02::Pattern01Bullet()
{
	Bullet02* newBullet = new Bullet02(transform->position, Vector3(0.4f, 0.4f, 0.4f), Vector3(0.f, -1.f, 0.f), false, 6.f);

	ObjectManager::AddObject(newBullet);

	MyCollisionManager::GetInstance()->RegisterObject(MyCollisionManager::ENEMY_BULLET, newBullet);

	canAttack = false;

	coolTime = 2.f;
}

void Enemy02::Pattern02Bullet()
{
	if (nullptr == target) return;

	if (target->isDead) return;

	Vector3 dir = target->transform->position - transform->position;

	Vector3::Normalize(&dir);

	Bullet02* newBullet = new Bullet02(transform->position, Vector3(0.4f, 0.4f, 0.4f), dir, false, 6.f);

	ObjectManager::AddObject(newBullet);

	MyCollisionManager::GetInstance()->RegisterObject(MyCollisionManager::ENEMY_BULLET, newBullet);

	canAttack = false;

	coolTime = 2.f;
}

void Enemy02::Pattern03Bullet()
{
	Vector3 dir[4] = { Vector3::UP, Vector3::DOWN, Vector3::LEFT, Vector3::RIGHT };
	Matrix rot;

	D3DXMatrixRotationZ(&rot, D3DXToRadian(45.f));

	for (int i = 0; i < 4; ++i)
	{
		if (2 == spawnPattern)
			D3DXVec3TransformNormal(&dir[i], &dir[i], &rot);

		Bullet02* newBullet = new Bullet02(transform->position, Vector3(0.4f, 0.4f, 0.4f), dir[i], false, 6.f);

		ObjectManager::AddObject(newBullet);

		MyCollisionManager::GetInstance()->RegisterObject(MyCollisionManager::ENEMY_BULLET, newBullet);
	}

	if (1 == spawnPattern)
	{
		spawnPattern = 2;
		canAttack = false;
		coolTime = 0.3f;
	}
	else
	{
		spawnPattern = 1;
		canAttack = false;
		coolTime = 3.f;
	}
}

void Enemy02::OnCollision(GameObject * from)
{
	Die();
}

bool Enemy02::Culling()
{
	if (1 == type)
	{
		Vector3 pos = transform->position;

		if (-5.f > pos.x || pos.x > 5.f || -4.f > pos.y) return true;
	}

	return false;
}
