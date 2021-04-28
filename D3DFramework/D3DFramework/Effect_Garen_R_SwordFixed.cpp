#include "stdafx.h"
#include "Effect_Garen_R_SwordFixed.h"

Effect_Garen_R_SwordFixed::Effect_Garen_R_SwordFixed()
{
	GetComponent(L"Mesh")->visible = false;
	GetComponent(L"renderer")->visible = false;

	transform->scale = { 0.04f, 0.04f, 0.04f };
	//transform->eulerAngles.x = D3DXToRadian(180.f);

	// meshSword
	CustomMesh* meshSword = RenderManager::CloneCustomMesh(L"garen_base_r_sword_plane");
	AddComponent(L"meshSword", meshSword);

	ForwardRenderer* rendererSword = new ForwardRenderer{ this, L"./forward.fx" };
	rendererSword->SetMesh(meshSword);
	rendererSword->SetDiffuseTextureParam("g_diffuseTexture");
	rendererSword->SetPass(0);
	AddComponent(L"rendererSword", rendererSword);

	meshSword->SetSubsetTexture(L"garen_base_r_sword_plane");

	// meshSwordEffect
	CustomMesh* meshSwordEffect = RenderManager::CloneCustomMesh(L"garen_base_r_sword_plane");
	AddComponent(L"meshSwordEffect", meshSwordEffect);
	
	ForwardRenderer* rendererSwordEffect = new ForwardRenderer{ this, L"./forward.fx" };
	rendererSwordEffect->SetMesh(meshSwordEffect);
	rendererSwordEffect->SetDiffuseTextureParam("g_diffuseTexture");
	rendererSwordEffect->SetPass(0);
	effectalpha = 0.5;
	rendererSwordEffect->SetAlpha(effectalpha);
	AddComponent(L"rendererSwordEffect", rendererSwordEffect);
	
	meshSwordEffect->SetSubsetTexture(L"garen_base_r_sword_plane_fire");
}

Effect_Garen_R_SwordFixed::~Effect_Garen_R_SwordFixed()
{
}

void Effect_Garen_R_SwordFixed::PostUpdate()
{
	StickToTarget();
	EffectObject::PostUpdate();
}

void Effect_Garen_R_SwordFixed::Update()
{
	EffectObject::Update();

	visible = tick < 0.4f ? false : true;
	if (!visible) return;

	if (tick < 0.8) return;

	auto rendererSword = dynamic_cast<ForwardRenderer*>(GetComponent(L"rendererSword"));
	swordalpha -= 2.f * Time::DeltaTime();
	rendererSword->SetAlpha(swordalpha);

	if (tick < 1.0) return;

	auto rendererSwordEffect = dynamic_cast<ForwardRenderer*>(GetComponent(L"rendererSwordEffect"));
	effectalpha -= 2.f * Time::DeltaTime();
	rendererSwordEffect->SetAlpha(effectalpha);
}
