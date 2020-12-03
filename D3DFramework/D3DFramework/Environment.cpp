#include "stdafx.h"
#include "Environment.h"
#include "Terrain.h"

Environment::Environment()
{
	//CustomMesh* mesh = (CustomMesh*)AddComponent<Terrain>(L"CustomMesh");
	//mesh->SetColor(D3DCOLOR_ARGB(255, 255, 255, 255));
	//mesh->SetTexture(TextureKey::GRASS);

	transform->scale = { 0.1f,0.1f, 0.1f };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	StaticMesh* smesh = RenderManager::CloneStaticMesh(L"summoner_rift");
	AddComponent(L"StaticMesh", smesh);
}

Environment::~Environment()
{
}

void Environment::Initialize()
{
}

void Environment::Release()
{
}

void Environment::Update()
{
	GameObject::Update();
}
