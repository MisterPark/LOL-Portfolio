#include "stdafx.h"
#include "Effect_Garen_E.h"
#include "FogOfWarRenderer.h"

Effect_Garen_E::Effect_Garen_E()
{
	GetComponent(L"Mesh")->visible =false;
	GetComponent(L"renderer")->visible=false;

	transform->scale = { 0.01f,0.01f, 0.01f };
	//transform->eulerAngles.x = D3DXToRadian(180.f);

	StaticMesh* mesh = RenderManager::CloneStaticMesh(L"garen_base_e_spin");
	AddComponent(L"StaticMesh", mesh);

	ForwardRenderer* renderer = new ForwardRenderer{ this, L"./forward.fx" };
	renderer->SetMesh(mesh);
	renderer->SetDiffuseTextureParam("g_diffuseTexture");
	AddComponent(L"renderer2", renderer);
}

Effect_Garen_E::~Effect_Garen_E()
{
}

void Effect_Garen_E::Update()
{
	GameObject::Update();
}
