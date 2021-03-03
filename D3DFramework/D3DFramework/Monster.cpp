#include "stdafx.h"
#include "Monster.h"
#include "Plane.h"
#include "Rectangle.h"
#include "MinionFloatingBar.h"
#include "MonsterAI.h"
#include "Collider.h"
#include "SphereCollider.h"

Monster::Monster()
{
	bar = (MinionFloatingBar*)SceneManager::GetCurrentScene()->CreateObject<MinionFloatingBar>(Layer::UI);
	bar->SetTarget(this);
	
	AddComponent<MonsterAI>(L"MonsterAI");
	collider->SetRadius(0.2f);
	collider->center = { 0.f,0.25f,0.f };
}

Monster::~Monster()
{
	bar = nullptr;
}

void Monster::Initialize()
{
	Unit::Initialize();
}

void Monster::Release()
{
	Unit::Release();
}

void Monster::Update()
{
	Unit::Update();
	
}

void Monster::OnCollisionEnter(Collider* target)
{
	if (dynamic_cast<Unit*>(target->gameObject))
	{
		Unit* unit = (Unit*)target->gameObject;
		if (unit->GetState() == UnitState::RUN)
		{
			unit->PushedOut(this);
		}

	}
}
