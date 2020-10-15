#include "stdafx.h"
#include "Boss02.h"
#include "Bullet02.h"
#include "Cube02.h"
#include "MyCollisionManager.h"

Boss02::Boss02()
{
}

Boss02::Boss02(Vector3 pos, Vector3 look, GameObject* tar) :
	target(tar)
{
	transform->position = pos;
	transform->look = look;

	moveSpeed = 1.f;

	Ready();
}

Boss02::~Boss02()
{
}

void Boss02::Ready()
{
	transform->scale = Vector3(2.f, 2.f, 2.f);

	IComponent* mesh = new Cube02(D3DCOLOR_XRGB(0, 0, 0));
	mesh->gameObject = this;
	components.emplace(L"Mesh", mesh);
}

void Boss02::Update()
{
	if (hp > 40)
	{
		ChangePhase(1);
	}
	else if (hp > 20)
	{
		ChangePhase(2);
	}
	else
	{
		ChangePhase(3);
	}

	switch (phase)
	{
	case 1: Phase01(); break;
	case 2: Phase02(); break;
	case 3: Phase03(); break;
	}
}

void Boss02::PostRender()
{
	Vector3 hpPos = transform->position;
	hpPos.x -= 0.1f;
	hpPos.y -= 0.4f;

	Vector3 winPos = Camera::WorldToScreenPoint(hpPos);

	TCHAR buffer[5] = L"";

	wsprintf(buffer, L"%d", hp);

	D2DRenderManager::DrawFont(buffer, winPos.x, winPos.y, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
}

void Boss02::Phase01()
{
	Chase();
	if (canAttack) Pattern01Bullet();
	else
	{
		coolTime -= TimeManager::DeltaTime();

		if (0.f > coolTime) canAttack = true;
	}
}

void Boss02::Phase02()
{
	if (canAttack) Pattern02Bullet();
	else
	{
		if (coolTime > 0.2f) Chase();
		coolTime -= TimeManager::DeltaTime();

		if (0.f > coolTime) canAttack = true;
	}
}

void Boss02::Phase03()
{
	if (canAttack) Pattern03Bullet();
	else
	{
		coolTime -= TimeManager::DeltaTime();

		if (0.f > coolTime) canAttack = true;
	}
}

void Boss02::Pattern01Bullet()
{
	Vector3 dir[4] = { { 0.f, -1.f, 0.f }, {0.f, 1.f, 0.f}, {1.f, 0.f, 0.f}, {-1.f, 0.f, 0.f} };
	Matrix rot;
	D3DXMatrixRotationZ(&rot, D3DXToRadian(angle));

	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3TransformNormal(&dir[i], &dir[i], &rot);

		Bullet02* newBullet = new Bullet02(transform->position, Vector3(0.4f, 0.4f, 0.4f), dir[i], false, 6.f);

		ObjectManager::AddObject(newBullet);

		MyCollisionManager::GetInstance()->RegisterObject(MyCollisionManager::ENEMY_BULLET, newBullet);
	}

	canAttack = false;

	angle -= 10.f;

	if (angle < -360.f)
	{
		angle = 0.f;
		coolTime = 2.f;
	}
	else coolTime = 0.1f;
}

void Boss02::Pattern02Bullet()
{
	Matrix rot;
	
	for (int i = 0; i < 15; ++i)
	{
		Vector3 dir = { 0.f, -1.f, 0.f };
		float degree = i * (360.f / 15.f) + ((spawnType % 2) * 12.f);
		D3DXMatrixRotationZ(&rot, D3DXToRadian(degree));
		D3DXVec3TransformNormal(&dir, &dir, &rot);

		Bullet02* newBullet = new Bullet02(transform->position, Vector3(0.6f, 0.6f, 0.6f), dir, false, 3.f);

		ObjectManager::AddObject(newBullet);

		MyCollisionManager::GetInstance()->RegisterObject(MyCollisionManager::ENEMY_BULLET, newBullet);
	}

	if (40 > spawnType)
	{
		canAttack = false;
		coolTime = 0.1f;
		++spawnType;
	}
	else
	{
		canAttack = false;
		coolTime = 3.f;
		spawnType = 0;
	}
}

void Boss02::Pattern03Bullet()
{
	Matrix rot;

	for (int i = 0; i < 15; ++i)
	{
		Vector3 dir = { 0.f, -1.f, 0.f };
		float degree = i * (360.f / 15.f) + (spawnType * 2.f);
		D3DXMatrixRotationZ(&rot, D3DXToRadian(degree));
		D3DXVec3TransformNormal(&dir, &dir, &rot);

		Bullet02* newBullet = new Bullet02(transform->position, Vector3(0.6f, 0.6f, 0.6f), dir, false, 3.f);

		ObjectManager::AddObject(newBullet);

		MyCollisionManager::GetInstance()->RegisterObject(MyCollisionManager::ENEMY_BULLET, newBullet);
	}

	if (45 > spawnType)
	{
		canAttack = false;
		coolTime = 0.1f;
		++spawnType;
	}
	else
	{
		canAttack = false;
		coolTime = 3.f;
		spawnType = 0;
	}
}

void Boss02::Chase()
{
	if (nullptr == target) return;

	if (target->isDead) return;

	Vector3 targetPos = target->transform->position;

	float xDist = targetPos.x - transform->position.x;
	xDist = fabsf(xDist);

	if (xDist < 0.05f) return;

	if (targetPos.x > transform->position.x)
	{
		MoveToTarget(transform->position + Vector3::RIGHT);
	}
	else
	{
		MoveToTarget(transform->position + Vector3::LEFT);
	}
}

void Boss02::ChangePhase(int input)
{
	if (input != phase)
	{
		phase = input;
		canAttack = false;
		coolTime = 2.f;
	}
}

void Boss02::OnCollision(GameObject * from)
{
	--hp;

	if (hp <= 0)
	{
		MyCollisionManager::GetInstance()->UnListObject(MyCollisionManager::BOSS, this);
		Die();
	}
}