#include "stdafx.h"
#include "Wall.h"
#include "MeshCollider.h"

Wall::Wall()
{
	isVisible = false;
	transform->scale = { 0.1f,0.1f, 0.1f };
	transform->Update();

	StaticMesh* smesh = RenderManager::CloneStaticMesh(L"nav_wall");
	AddComponent(L"NavMesh", smesh);
	AddComponent<MeshCollider>(L"MeshCollider");
}

Wall::~Wall()
{
}

void Wall::Initialize()
{
}

void Wall::Release()
{
}

void Wall::Update()
{
	GameObject::Update();

	if (InputManager::GetKeyDown('L'))
	{
		isVisible = !isVisible;
	}
}
