#include "stdafx.h"
#include "Effect_Garen_R_SwordMove.h"

Effect_Garen_R_SwordMove::Effect_Garen_R_SwordMove()
{
	GetComponent(L"Mesh")->visible = false;
	GetComponent(L"renderer")->visible = false;

	transform->scale = { 0.02f, 0.02f, 0.02f };
	offset = { 0.f,5.f,0.f };
	//transform->eulerAngles.x = D3DXToRadian(180.f);

	// meshSwordMove
	CustomMesh* meshSwordMove = RenderManager::CloneCustomMesh(L"garen_base_r_sword_plane");
	AddComponent(L"meshSwordMove", meshSwordMove);

	ForwardRenderer* rendererSwordMove = new ForwardRenderer{ this, L"./forward.fx" };
	rendererSwordMove->SetMesh(meshSwordMove);
	rendererSwordMove->SetDiffuseTextureParam("g_diffuseTexture");
	AddComponent(L"rendererSwordMove", rendererSwordMove);
	rendererSwordMove->SetPass(0);

	meshSwordMove->SetSubsetTexture(L"garen_base_r_sword_plane");
}

Effect_Garen_R_SwordMove::~Effect_Garen_R_SwordMove()
{
}

void Effect_Garen_R_SwordMove::PostUpdate()
{
	StickToTarget();
	EffectObject::PostUpdate();
}

void Effect_Garen_R_SwordMove::Update()
{
	EffectObject::Update();

	visible = tick < 0.2f ? false : true;
	if (!visible) return;

	offset.y -= 20.f * Time::DeltaTime();
}
