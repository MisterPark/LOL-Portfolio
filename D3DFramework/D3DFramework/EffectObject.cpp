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
	int a = 10;
}

void EffectObject::Initialize()
{
}

void EffectObject::Release()
{
}

void EffectObject::Update()
{
	if (tick >= duration)
	{
		Destroy();
	}
	GameObject::Update();
	tick += Time::DeltaTime();
}

void EffectObject::RotationBillboard()
{
	Billboard();
	transform->Update();

	if (target == nullptr) return;
	float angleY = Vector3::AngleY(transform->position, target->transform->position);
	angle = -angleY + D3DXToRadian(180.f);
	transform->RotateYaw(angle);
}

void EffectObject::ChaseTarget()
{
	if (target == nullptr) return;

	Vector3 targetPos = target->transform->position;
	targetPos += offset;
	Vector3 to = targetPos - transform->position;
	transform->position += to.Normalized() * speed * Time::DeltaTime();
}

void EffectObject::StickToTarget()
{
	if (target == nullptr)return;

	transform->position = target->transform->position + offset;
}

void EffectObject::SetTarget(GameObject* _target)
{
	target = _target;
}

void EffectObject::SetOffset(Vector3 _offset)
{
	offset = _offset;
}

void EffectObject::SetDuration(float _duration)
{
	this->duration = _duration;
}
