#include "stdafx.h"
#include "Bullet02.h"
#include "Cube02.h"
#include "MyCollisionManager.h"

Bullet02::Bullet02()
{
}

Bullet02::Bullet02(Vector3 pos, Vector3 scale, Vector3 look, bool isPlayer, float speed) :
	isPlayerType(isPlayer)
{
	transform->position = pos;
	transform->scale = scale;
	dir = look;
	moveSpeed = speed;

	Ready();
}

Bullet02::~Bullet02()
{
}

void Bullet02::Ready()
{
	if (isPlayerType)
	{
		IComponent* newCube = new Cube02(D3DCOLOR_XRGB(255, 255, 0));
		newCube->gameObject = this;
		components.emplace(L"Mesh", newCube);
	}
	else
	{
		IComponent* newCube = new Cube02(D3DCOLOR_XRGB(255, 0, 0));
		newCube->gameObject = this;
		components.emplace(L"Mesh", newCube);
	}
}

void Bullet02::Update()
{
	MoveToTarget(transform->position + dir);

	for (auto& iter : components)
	{
		iter.second->Update();
	}
}

bool Bullet02::Culling()
{
	Vector3 pos = transform->position;

	if (-5.f > pos.x || pos.x > 5.f || -5.f > pos.y || pos.y > 5.f)
	{
		Die();
		return true;
	}

	return false;
}

void Bullet02::OnCollision(GameObject * from)
{
	Die();
}
