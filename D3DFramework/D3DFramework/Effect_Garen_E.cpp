#include "stdafx.h"
#include "Effect_Garen_E.h"
#include "FogOfWarRenderer.h"

Effect_Garen_E::Effect_Garen_E()
{
	
	DeleteComponent(L"Mesh");
	DeleteComponent(L"renderer");

	transform->scale = { 0.02f,0.02f, 0.02f };
	//transform->eulerAngles.x = D3DXToRadian(180.f);

	CustomMesh* mesh = RenderManager::CloneCustomMesh(L"garen_base_e_spin");
	AddComponent(L"CustomMesh", mesh);

	ForwardRenderer* renderer = new ForwardRenderer{ this, L"./forward.fx" };
	renderer->SetMesh(mesh);
	renderer->SetDiffuseTextureParam("g_diffuseTexture");
	renderer->SetPass(1);
	AddComponent(L"renderer2", renderer);

	mesh->SetSubsetTexture(L"garen_base_e_spin_edge");
}

Effect_Garen_E::~Effect_Garen_E()
{
}

void Effect_Garen_E::PostUpdate()
{
	StickToTarget();
	transform->eulerAngles.y += (D3DXToRadian(720.f) * Time::DeltaTime());
	EffectObject::PostUpdate();
}
