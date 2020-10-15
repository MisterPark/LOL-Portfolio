#include "stdafx.h"
#include "Player02.h"
#include "Cube02.h"
#include "Bullet02.h"
#include "MyCollisionManager.h"

Player02::Player02()
{
	IComponent* mesh = new Cube02(D3DCOLOR_XRGB(255, 255, 255));
	mesh->gameObject = this;
	components.emplace(L"Mesh", mesh);

	moveSpeed = 3.f;
}

Player02::~Player02()
{
}

void Player02::Update()
{
	if (!canAttack)
	{
		coolTime -= TimeManager::DeltaTime();

		if (0.f > coolTime) canAttack = true;
	}

	if (InputManager::GetKey('Z'))
	{
		Attack();
	}
	if (InputManager::GetKeyDown('X'))
	{
		isInvincible ^= true;
	}

	if (InputManager::GetKey(VK_UP))
	{
		float futureValue = transform->position.y + (moveSpeed * TimeManager::DeltaTime());

		if (futureValue <= 2.9f) MoveToTarget(transform->position + Vector3::UP);
	}
	if (InputManager::GetKey(VK_DOWN))
	{
		float futureValue = transform->position.y - (moveSpeed * TimeManager::DeltaTime());

		if(futureValue >= -2.9f) MoveToTarget(transform->position + Vector3::DOWN);
	}
	if (InputManager::GetKey(VK_LEFT))
	{
		float futureValue = transform->position.x - (moveSpeed * TimeManager::DeltaTime());

		if(futureValue >= -3.9f) MoveToTarget(transform->position + Vector3::LEFT);
	}
	if (InputManager::GetKey(VK_RIGHT))
	{
		float futureValue = transform->position.x + (moveSpeed * TimeManager::DeltaTime());

		if (futureValue <= 3.9f) MoveToTarget(transform->position + Vector3::RIGHT);
	}

	for (auto& iter : components)
	{
		iter.second->Update();
	}
}

void Player02::Attack()
{
	if (canAttack)
	{
		Bullet02* newBullet = new Bullet02(transform->position, Vector3(0.4f, 0.4f, 0.4f), transform->up, true, 10.f);
		ObjectManager::AddObject(newBullet);

		MyCollisionManager::GetInstance()->RegisterObject(MyCollisionManager::PLAYER_BULLET, newBullet);

		canAttack = false;
		coolTime = 0.3f;
	}
}

void Player02::OnCollision(GameObject * from)
{
	if (!isInvincible)
	{
		--hp;

		if (hp <= 0)
		{
			MyCollisionManager::GetInstance()->UnListObject(MyCollisionManager::PLAYER, this);
			Die();
		}
	}
}

void Player02::PostRender()
{
	Vector3 hpPos = transform->position;
	hpPos.x -= 0.1f;
	hpPos.y -= 0.2f;
	
	Vector3 winPos = Camera::WorldToScreenPoint(hpPos);

	TCHAR buffer[5] = L"";

	wsprintf(buffer, L"%d", hp);

	D2DRenderManager::DrawFont(buffer, winPos.x, winPos.y, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));
}
