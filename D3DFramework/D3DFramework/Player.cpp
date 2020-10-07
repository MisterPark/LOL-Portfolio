#include "stdafx.h"
#include "Player.h"
#include "IComponent.h"
#include "Mesh.h"

using namespace PKH;

PKH::Player::Player()
{
	moveSpeed = 3.f;
}

PKH::Player::~Player()
{
}

void PKH::Player::Update()
{
	if (InputManager::GetKey(VK_UP))
	{
		Transform* trans = (Transform*)GetComponent(L"Transform");
		Vector3 target = trans->target + trans->position;
		Move(target);
	}
	if (InputManager::GetKey(VK_DOWN))
	{
		Transform* trans = (Transform*)GetComponent(L"Transform");
		Vector3 target = -trans->target + transform->position;
		Move(target);
	}
	if (InputManager::GetKey(VK_LEFT))
	{
		Transform* trans = (Transform*)GetComponent(L"Transform");
		Move(trans->position + PKH::Vector3(-1,0,0));
	}
	if (InputManager::GetKey(VK_RIGHT))
	{
		Transform* trans = (Transform*)GetComponent(L"Transform");
		Move(trans->position + PKH::Vector3(1, 0, 0));
	}
	if (InputManager::GetKey('Z'))
	{
		Transform* trans = (Transform*)GetComponent(L"Transform");
		Move(trans->position + PKH::Vector3(0, 0, 1));
	}
	if (InputManager::GetKey('X'))
	{
		Transform* trans = (Transform*)GetComponent(L"Transform");
		Move(trans->position + PKH::Vector3(0, 0, -1));
	}

	if (InputManager::GetKey(VK_NUMPAD7))
	{
		transform->rotation.x += TimeManager::DeltaTime();
	}
	if (InputManager::GetKey(VK_NUMPAD4))
	{
		transform->rotation.x -= TimeManager::DeltaTime();
	}
	if (InputManager::GetKey(VK_NUMPAD8))
	{
		transform->rotation.y += TimeManager::DeltaTime();
	}
	if (InputManager::GetKey(VK_NUMPAD5))
	{
		transform->rotation.y -= TimeManager::DeltaTime();
	}
	if (InputManager::GetKey(VK_NUMPAD9))
	{
		transform->rotation.z += TimeManager::DeltaTime();
	}
	if (InputManager::GetKey(VK_NUMPAD6))
	{
		transform->rotation.z -= TimeManager::DeltaTime();
	}

	for (auto& comp : components)
	{
		comp.second->Update();
	}
}

void PKH::Player::Render()
{
	for (auto& comp : components)
	{
		Mesh* mesh = dynamic_cast<Mesh*>(comp.second);
		if (mesh == nullptr) continue;

		mesh->Render();
	}
}
