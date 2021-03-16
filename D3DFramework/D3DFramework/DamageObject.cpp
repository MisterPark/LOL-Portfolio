#include "stdafx.h"
#include "DamageObject.h"
#include "Plane.h"
#include "Rectangle.h"
#include "MinionFloatingBar.h"
#include "Collider.h"
#include "SphereCollider.h"
#include "DamageCalc.h"

DamageObject::DamageObject()
{
	
}

DamageObject::~DamageObject()
{
	for (auto calc : damageCalcList)
	{
		delete calc;
	}
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

	ObjectFollowMove();
	Calc_StartOfInterval();

	GameObject::Update();
}

void DamageObject::OnCollisionEnter(Collider* target)
{
	Unit* pUnit = dynamic_cast<Unit*>(target->gameObject);
	if (pUnit == nullptr)
		return;
	if (team == pUnit->team)
		return;

	if (attackCheck && !Check_DamagedOverlap(target->gameObject)) {
		//float damage = pUnit->stat->GetValue(StatType::AttackDamage);
		float damage = attackDamage;// hostObject->stat->GetValue(StatType::AttackDamage);
		Calc_FinalDamage(&damage, hostObject->stat, pUnit->stat);
		pUnit->SetLastAttacker(hostObject);
		pUnit->TakeDamage(damage);
		damagedObject.emplace_back(target->gameObject);
	}
}

void DamageObject::Set_DamageObject(Unit* _hostObject, Vector3 _pos, float _scale, Team _team, float _attack, float _lifeTime, float _interval, float _interval_AttackTime, float _startTime) {
	hostObject = _hostObject;
	*transform->Get_Pos() = _pos;
	collider = (SphereCollider*)AddComponent<SphereCollider>(L"SphereCollider");
	collider->SetRadius(_scale);
	team = _team;
	attackDamage = _attack;
	lifeTime = _lifeTime;
	interval_Init = _interval;
	interval_Attack_Init = _interval_AttackTime;
	startTime = _startTime;
	if (startTime <= 0.f)
		attackCheck = true;

}

void DamageObject::Set_ObjectFollow(Unit* _object)
{
	followObject = _object;
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

void DamageObject::Add_DamageCalc(DamageCalc* _damageCalc)
{
	damageCalcList.emplace_back(_damageCalc);
}

void DamageObject::ObjectFollowMove()
{
	if (followObject != nullptr)
	{
		*transform->Get_Pos() = followObject->transform->GetPos();
	}
}

void DamageObject::Calc_StartOfInterval()
{
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
}

void DamageObject::Calc_FinalDamage(float* _damage, Stat* _myStat, Stat* _targetStat)
{
	for (auto& calc : damageCalcList)
	{
		calc->Calc(_damage, _myStat, _targetStat);
	}
}