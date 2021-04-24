#include "stdafx.h"
#include "Effect_Garen_Q_Impact.h"

Effect_Garen_Q_Impact::Effect_Garen_Q_Impact()
{
	GetComponent(L"Mesh")->visible = false;
	GetComponent(L"renderer")->visible = false;

	offset = { 0.f, 0.f, 0.f };
	transform->scale = { 0.3f, 0.5f, 0.5f };
	//transform->eulerAngles.y = -D3DXToRadian(30.f);
	transform->RotateRoll(D3DXToRadian(30.f));

	// meshSwordMove
	CustomMesh* mesh = RenderManager::CloneCustomMesh(L"garen_base_q_impact");
	AddComponent(L"CustomMesh", mesh);

	ForwardRenderer* renderer = new ForwardRenderer{ this, L"./forward.fx" };
	renderer->SetMesh(mesh);
	renderer->SetDiffuseTextureParam("g_diffuseTexture");
	AddComponent(L"CustomRenderer", renderer);

	mesh->SetSubsetTexture(L"garen_base_q_tar_impact");
}

Effect_Garen_Q_Impact::~Effect_Garen_Q_Impact()
{
}

void Effect_Garen_Q_Impact::PostUpdate()
{
	StickToTarget();
	EffectObject::PostUpdate();
}

void Effect_Garen_Q_Impact::Update()
{
	EffectObject::Update();

	visible = false;
	
	if (tick < 0.2f) return;
	
	visible = true;

	auto renderer = dynamic_cast<ForwardRenderer*>(GetComponent(L"CustomRenderer"));
	if (renderer == nullptr) return;

}
