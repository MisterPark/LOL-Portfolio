#include "stdafx.h"
#include "Effect_Garen_W_Shield.h"

Effect_Garen_W_Shield::Effect_Garen_W_Shield()
{
	transform->scale = { 0.02f, 0.02f, 0.02f };

	CustomMesh* meshShield = RenderManager::CloneCustomMesh(L"garen_base_w_shield");
	AddComponent(L"meshShield", meshShield);

	ForwardRenderer* rendererShield = new ForwardRenderer{ this, L"./forward.fx" };
	rendererShield->SetMesh(meshShield);
	rendererShield->SetDiffuseTextureParam("g_diffuseTexture");
	rendererShield->SetPass(0);
	AddComponent(L"rendererShield", rendererShield);

	meshShield->SetSubsetTexture(L"garen_base_w_shield_txt");
}

Effect_Garen_W_Shield::~Effect_Garen_W_Shield()
{
}

void Effect_Garen_W_Shield::PostUpdate()
{
	StickToTarget();
	


	GameObject::PostUpdate();
}

void Effect_Garen_W_Shield::Update()
{
	EffectObject::Update();

	auto renderer = dynamic_cast<ForwardRenderer*>(GetComponent(L"rendererShield"));
	if (renderer == nullptr)
		return;

	renderer->SetAlpha(1- (tick / duration));
}
