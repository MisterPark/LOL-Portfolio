#include "stdafx.h"
#include "Effect_Garen_R_Dome.h"

Effect_Garen_R_Dome::Effect_Garen_R_Dome()
{
	GetComponent(L"Mesh")->visible = false;
	GetComponent(L"renderer")->visible = false;

	scale = 0.02f;
	transform->scale = { scale, scale, scale };
	offset = { 0.f,1.f,0.f };
	//transform->eulerAngles.x = D3DXToRadian(180.f);

	// meshSwordMove
	CustomMesh* mesh = RenderManager::CloneCustomMesh(L"garen_base_r_halfdome");
	AddComponent(L"CustomMesh", mesh);

	ForwardRenderer* renderer = new ForwardRenderer{ this, L"./forward.fx" };
	renderer->SetMesh(mesh);
	renderer->SetDiffuseTextureParam("g_diffuseTexture");
	AddComponent(L"CustomRenderer", renderer);
	renderer->SetPass(1);
	alpha = 0.3f;
	renderer->SetAlpha(alpha);

	mesh->SetSubsetTexture(L"garen_base_r_dome_color");
}

Effect_Garen_R_Dome::~Effect_Garen_R_Dome()
{
}

void Effect_Garen_R_Dome::PostUpdate()
{
	StickToTarget();
	EffectObject::PostUpdate();
}

void Effect_Garen_R_Dome::Update()
{
	EffectObject::Update();

	auto renderer = dynamic_cast<ForwardRenderer*>(GetComponent(L"CustomRenderer"));
	if (renderer == nullptr) return;

	visible = false;

	if (tick < 0.5) return;

	visible = true;

	scale += 0.02 * Time::DeltaTime();
	transform->scale = { scale, scale, scale };

	if (tick < 0.9) return;

	alpha -= 5 * Time::DeltaTime();
}
