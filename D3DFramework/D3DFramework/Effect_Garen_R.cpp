﻿#include "stdafx.h"
#include "Effect_Garen_R.h"

Effect_Garen_R::Effect_Garen_R()
{
	GetComponent(L"Mesh")->visible = false;
	GetComponent(L"renderer")->visible = false;

	transform->scale = { 0.01f,0.01f, 0.01f };
	//transform->eulerAngles.x = D3DXToRadian(180.f);

	StaticMesh* mesh = RenderManager::CloneStaticMesh(L"garen_base_r_sword_plane");
	AddComponent(L"StaticMesh", mesh);

	ForwardRenderer* renderer = new ForwardRenderer{ this, L"./forward.fx" };
	renderer->SetMesh(mesh);
	renderer->SetDiffuseTextureParam("g_diffuseTexture");
	AddComponent(L"renderer2", renderer);

	mesh->SetSubsetTexture(0, L"garen_base_r_sword_plane");
}

Effect_Garen_R::~Effect_Garen_R()
{
}

void Effect_Garen_R::Update()
{
	GameObject::Update();
}
