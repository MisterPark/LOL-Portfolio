#include "stdafx.h"
#include "NavMeshMap.h"
#include "MeshCollider.h"

NavMeshMap::NavMeshMap()
{
	//isVisible = false;
	transform->scale = { 0.1f,0.1f, 0.1f };
	//transform->eulerAngles.y = D3DXToRadian(180.f);
	StaticMesh* smesh = RenderManager::CloneStaticMesh(L"summoner_rift_nav");
	AddComponent(L"StaticMesh", smesh);
	AddComponent<MeshCollider>(L"MeshCollider");
}

NavMeshMap::~NavMeshMap()
{
}

void NavMeshMap::Initialize()
{
}

void NavMeshMap::Release()
{
}

void NavMeshMap::Update()
{
	GameObject::Update();

	if (InputManager::GetKeyDown('P'))
	{
		isVisible = !isVisible;
	}
}
