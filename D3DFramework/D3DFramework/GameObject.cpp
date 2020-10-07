#include "stdafx.h"
#include "GameObject.h"
#include "IComponent.h"
#include "transform.h"

using namespace PKH;

PKH::GameObject::GameObject()
{
	transform = (Transform*)AddComponent<Transform>(L"Transform");
}

PKH::GameObject::~GameObject()
{
}

void PKH::GameObject::Update()
{
}

void PKH::GameObject::Render()
{
}

void PKH::GameObject::Die()
{
	isDead = true;
}

void PKH::GameObject::OnCollision(GameObject* target)
{
}


void PKH::GameObject::Move(Vector3 _target)
{
	Vector3 dir = _target - transform->position;
	Vector3::Normalize(&dir);
	transform->position.x += dir.x * moveSpeed * TimeManager::DeltaTime();
	transform->position.y += dir.y * moveSpeed * TimeManager::DeltaTime();
	transform->position.z += dir.z * moveSpeed * TimeManager::DeltaTime();
}

IComponent* PKH::GameObject::GetComponent(const wstring& _key)
{
	auto f = components.find(_key);
	if (f == components.end()) return nullptr;
	return f->second;
}

