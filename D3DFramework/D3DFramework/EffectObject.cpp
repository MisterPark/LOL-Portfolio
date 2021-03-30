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
	Billboard();
	transform->Update();
	
	Vector3 axis = transform->up;

	static float angle = 0.f;

	if (Input::GetKeyDown('N'))
	{
		angle += D3DXToRadian(1.f);
	}

	transform->RotateYaw(angle);

	GameObject::Update();
}
