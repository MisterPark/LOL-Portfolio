#include "stdafx.h"
#include "EffectObject.h"
#include "Rectangle.h"

EffectObject::EffectObject()
{
	Engine::Plane* mesh = (Engine::Plane*)AddComponent<Engine::Plane>(L"Mesh");
	ForwardRenderer* renderer = new ForwardRenderer{ this, L"./forward.fx" };
	renderer->SetMesh(mesh);
	renderer->SetDiffuseTextureParam("g_diffuseTexture");
	AddComponent(L"renderer", renderer);
}

EffectObject::~EffectObject()
{
}

void EffectObject::Initialize()
{
}

void EffectObject::Release()
{
}

void EffectObject::Update()
{
	//Billboard();
	Vector3 camDir = { 0,2,-1 };
	Vector3::Normalize(&camDir);
	camDir = -camDir;
	//transform->Rotate(camDir);

	static float angle = 0.f;
	if (Input::GetKeyDown('N'))
	{
		angle = angle + D3DXToRadian(1.f);
	}
	transform->Rotate(camDir, angle);
	//transform->LookAt(Camera::main->transform->position);
	GameObject::Update();
}
