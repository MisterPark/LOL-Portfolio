#include "stdafx.h"
#include "Environment.h"
#include "Terrain.h"

Environment::Environment()
{
	CustomMesh* mesh = (CustomMesh*)AddComponent<Terrain>(L"CustomMesh");
	mesh->SetColor(D3DCOLOR_ARGB(255, 255, 255, 255));
	mesh->SetTexture(TextureKey::GRASS);
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
