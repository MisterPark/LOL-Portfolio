#include "stdafx.h"
#include "Environment.h"
#include "Terrain.h"
#include "GameRenderer.h"
Environment::Environment()
{
	//CustomMesh* mesh = (CustomMesh*)AddComponent<Terrain>(L"CustomMesh");
	//mesh->SetColor(D3DCOLOR_ARGB(255, 255, 255, 255));
	//mesh->SetTexture(TextureKey::GRASS);

	transform->scale = { 0.1f,0.1f, 0.1f };
	//transform->eulerAngles.y = D3DXToRadian(180.f);
	TerrainMesh* mesh = RenderManager::CloneTerrainMesh(L"summoner_rift");
	AddComponent(L"TerrainMesh", mesh);
	mesh->renderGroupID = RenderGroupID::Deferred;
	GameRenderer::Register(mesh);
	
}

Environment::~Environment()
{
	TerrainMesh* mesh = static_cast<TerrainMesh*>(this->GetComponent< TerrainMesh>());
	if (mesh != nullptr)
	{
		GameRenderer::Unregister(mesh);
	}
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
