#include "stdafx.h"
#include "TurretMissileBase.h"
#include "Plane.h"
#include "ForwardRenderer.h"

TurretMissileBase::TurretMissileBase()
{
	mesh = (Engine::Plane*)AddComponent<Engine::Plane>(L"Mesh");
	mesh->SetTexture(L"sru_chaos_cm_ba_mis_tex");
	mesh->SetBlendMode(BlendMode::ALPHA_BLEND);
	mesh->SetCullMode(CullMode::NONE);
	transform->scale = { 0.75f,0.75f, 0.75f };
	ForwardRenderer* renderer = new ForwardRenderer{ this, L"./forward.fx" };
	renderer->SetMesh(mesh);
	renderer->SetDiffuseTextureParam("g_diffuseTexture");
	AddComponent(L"renderer", renderer);
}

TurretMissileBase::~TurretMissileBase()
{
}

void TurretMissileBase::Initialize()
{
}

void TurretMissileBase::Release()
{
}

void TurretMissileBase::Update()
{
	Billboard();
	GameObject::Update();
}
