#include "stdafx.h"
#include "Unit.h"
#include "SphereCollider.h"
#include "NavMeshAgent.h"
#include "Animation.h"

Unit::Unit()
{
	anim = (Animation*)AddComponent<Animation>(L"Animation");
	SphereCollider* collider = (SphereCollider*)AddComponent<SphereCollider>(L"SphereCollider");
	collider->radius = 1.5f;
	collider->center = { 0.f,1.f,0.f };

	AddComponent< NavMeshAgent>(L"NavMeshAgent");
}

Unit::~Unit()
{
}

void Unit::Initialize()
{
}

void Unit::Release()
{
}

void Unit::Update()
{
	state = UnitState::IDLE1;

	GameObject::Update();
}
