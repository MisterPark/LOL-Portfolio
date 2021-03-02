#include "stdafx.h"
#include "DamageObject.h"
#include "Plane.h"
#include "Rectangle.h"
#include "MinionFloatingBar.h"
#include "Collider.h"
#include "SphereCollider.h"

DamageObject::DamageObject()
{
	
}

DamageObject::~DamageObject()
{
	
}

void DamageObject::Initialize()
{
	
}

void DamageObject::Release()
{
	
}

void DamageObject::Update()
{
	if (lifeTime < 0.f) {
		Destroy();
		return;
	}
	float deltaTime = Time::DeltaTime();
	lifeTime -= deltaTime;

	if (startTime <= 0.f) {
		if (interval_Init != 0.f) {
			interval_Time -= deltaTime;
			if (interval_Time <= 0.f) {
				interval_Time = interval_Init;
				interval_Attack_Time = interval_Attack_Init;
				attackCheck = true;
				damagedObject.clear();
			}
		}

		if (interval_Attack_Init != -1.f && attackCheck) {
			interval_Attack_Time -= deltaTime;
			if (interval_Attack_Time <= 0.f) {
				interval_Attack_Time = interval_Attack_Init;
				attackCheck = false;
			}
		}
	}
	else {
		startTime -= deltaTime;
	}

	GameObject::Update();
}

void DamageObject::OnCollisionEnter(Collider* target)
{
	/*if (dynamic_cast<Unit*>(target->gameObject))
	{
		Unit* unit = (Unit*)target->gameObject;
		if (unit->GetState() == UnitState::RUN)
		{
			unit->PushedOut(this);
		}

	}*/
	Unit* pUnit = dynamic_cast<Unit*>(target->gameObject);
	if (pUnit == nullptr)
		return;
	if (team == pUnit->team)
		return;

	if (!Check_DamagedOverlap(target->gameObject)) {
		pUnit->SetLastAttacker(hostObject);
		pUnit->TakeDamage(attackDamage.GetValue());
		damagedObject.emplace_back(target->gameObject);
	}
}

void DamageObject::Set_DamageObject(Unit* _hostObject, Vector3 _pos, float _scale, Team _team, float _attack, float _lifeTime, float _interval, float _interval_AttackTime, float _startTime) {
	hostObject = _hostObject;
	*transform->Get_Pos() = _pos;
	SphereCollider* sphereCol = (SphereCollider*)AddComponent<SphereCollider>(L"SphereCollider");
	sphereCol->SetRadius(_scale);
	team = _team;
	attackDamage = _attack;
	lifeTime = _lifeTime;
	interval_Init = _interval;
	interval_Attack_Init = _interval_AttackTime;
	startTime = _startTime;
	if (startTime < 0.f)
		attackCheck = true;

}

bool DamageObject::Check_DamagedOverlap(GameObject* pDamagedObject)
{
	for (auto& obj : damagedObject)
	{
		if (obj == pDamagedObject)
			return true;
	}
	return false;
}