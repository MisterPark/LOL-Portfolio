﻿#include "stdafx.h"
#include "DamageObject_Garen_E.h"
#include "Unit.h"
#include "Collider.h"
#include "SphereCollider.h"
#include "Buff_GarenEArmorDec.h"

DamageObject_Garen_E::DamageObject_Garen_E()
{
}

DamageObject_Garen_E::~DamageObject_Garen_E()
{

}

void DamageObject_Garen_E::Initialize()
{

}

void DamageObject_Garen_E::Release()
{
}

void DamageObject_Garen_E::Update()
{
	if (isDead) {
		Destroy();
		return;
	}
	
	TakeDamage();
	ObjectFollowMove();
	Calc_StartOfInterval();

	GameObject::Update();
}

void DamageObject_Garen_E::OnCollisionEnter(Collider* target)
{
	Unit* pUnit = dynamic_cast<Unit*>(target->gameObject);
	if (pUnit == nullptr)
		return;
	if (team == pUnit->team)
		return;

	if (attackCheck && !Check_DamagedOverlap(target->gameObject)) {
		if(proximateUnit == nullptr)
			proximateUnit = (Unit*)target->gameObject;
		else {
			Vector3 myWorldPos = collider->GetWorldPosition();
			Vector3 targetWorldPos = target->GetWorldPosition();
			Vector3 proximateWorldPos = proximateUnit->collider->GetWorldPosition();
			float targetDistance = Vector3::Distance(myWorldPos, targetWorldPos);
			float proximateDistance = Vector3::Distance(myWorldPos, targetWorldPos);
			if (targetDistance < proximateDistance)
				proximateUnit = (Unit*)target->gameObject;
		}
		tempHitList.emplace_back(target->gameObject);

		Unit* targetUnit = dynamic_cast<Unit*>(target->gameObject);
		if(targetUnit != nullptr)
			damageExpected.emplace_back(targetUnit);
	}

	Check_TotalHitList((Unit*)target->gameObject);
}

void DamageObject_Garen_E::TakeDamage()
{
	if (proximateUnit == nullptr)
		return;
	float baseDamage = attackDamage;
	for (auto& unit : damageExpected)
	{
		float damage = baseDamage;
		Calc_FinalDamage(&damage, host->stat, unit->stat);
		unit->SetLastAttacker(host);
		unit->OnDamaged(host, hostSkill, &damage);
		host->OnHit(host, hostSkill);
		unit->TakeDamage(damage);
		Buff_GarenEArmorDec* attackBuff = new Buff_GarenEArmorDec(host, 6.f);
		unit->stat->AddBuff(attackBuff);

		// 피격정보 저장
		Unit::HitInfo info;
		info.damageSum += damage;
		info.unit = host;

		auto iter = unit->hitList.begin();
		auto end = unit->hitList.end();
		for (; iter != end;)
		{
			if ((*iter).unit == host)
			{
				info.damageSum += (*iter).damageSum;
				iter = unit->hitList.erase(iter);
				break;
			}
			++iter;
		}

		unit->hitList.push_back(info);
	}
	//front 가장가까운적 추가피해
	float damage = baseDamage * 1.f;//0.25f;
	Calc_FinalDamage(&damage, host->stat, proximateUnit->stat);
	proximateUnit->OnDamaged(host, hostSkill, &damage);
	proximateUnit->TakeDamage(damage);

	damageExpected.clear();
	proximateUnit = nullptr;

};