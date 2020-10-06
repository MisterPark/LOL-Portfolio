#include "stdafx.h"
#include "Player.h"
#include "IComponent.h"
#include "Mesh.h"

using namespace PKH;

PKH::Player::Player()
{
	transform.position.z = 3.f;
}

PKH::Player::~Player()
{
}

void PKH::Player::Update()
{
	if (InputManager::GetKey(VK_UP))
	{
		this->transform.position.y += 3.f * TimeManager::DeltaTime();
	}
	if (InputManager::GetKey(VK_DOWN))
	{
		this->transform.position.y -= 3.f * TimeManager::DeltaTime();
	}
	if (InputManager::GetKey(VK_LEFT))
	{
		this->transform.position.x -= 3.f * TimeManager::DeltaTime();
	}
	if (InputManager::GetKey(VK_RIGHT))
	{
		this->transform.position.x += 3.f * TimeManager::DeltaTime();
	}
	if (InputManager::GetKey('Z'))
	{
		this->transform.position.z -= 3.f * TimeManager::DeltaTime();
	}
	if (InputManager::GetKey('X'))
	{
		this->transform.position.z += 3.f * TimeManager::DeltaTime();
	}


	if (InputManager::GetKey(VK_NUMPAD6))
	{
		this->transform.rotation.x -= 1.f * TimeManager::DeltaTime();
	}
	if (InputManager::GetKey(VK_NUMPAD8))
	{
		this->transform.rotation.y -= 1.f * TimeManager::DeltaTime();
	}
	if (InputManager::GetKey(VK_NUMPAD5))
	{
		this->transform.rotation.z -= 1.f * TimeManager::DeltaTime();
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
