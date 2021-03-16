#include "stdafx.h"
#include "Skill_Garen_E.h"
#include "Unit.h"
#include "Buff.h"
#include "DamageObject_Garen_E.h"
#include "DamageCalc_Basic.h"
#include "Buff_GarenEDamage.h"
#include "Buff.h"

Skill_Garen_E::Skill_Garen_E(Unit* _hostUnit)
{
	coolTime_Init = 2.f;
	duration = 3.f;
	hostUnit = _hostUnit;
}

Skill_Garen_E::~Skill_Garen_E()
{
}

void Skill_Garen_E::Start()
{
	Skill::Start();

	DamageObject_Garen_E* damageObj = (DamageObject_Garen_E*)SceneManager::GetCurrentScene()->CreateObject<DamageObject_Garen_E>(Layer::Unit);
	float attackDamage = 40.f + hostUnit->stat->GetValue(StatType::AttackDamage) * 0.32f;
	float attackInterval = 3.f / 7.f;// + TODO: 아이템과 레벨업으로 인한 추가공격횟수 추가해줘야함
	damageObj->Set_DamageObject(hostUnit, hostUnit->transform->GetPos(), 7.f, hostUnit->team, attackDamage, duration, attackInterval);
	damageObj->Set_ObjectFollow(hostUnit);
	//제일처음에 Basic만 잘 입혀줄것
	damageObj->Add_DamageCalc(DamageCalc_Basic::CreateCalc());

	damageBuff = new Buff_GarenEDamage(hostUnit, 3.f, damageObj);//reductionValue);
	hostUnit->stat->AddBuff(damageBuff);
	coolTime = coolTime_Init;

}

void Skill_Garen_E::Passive()
{
	if (coolTime > 0.f) {
		coolTime -= Time::DeltaTime();
	}

}

void Skill_Garen_E::Active()
{
	//if (!active)
		//return;

	if (tick <= 0.f) {
		End();
		return;
	}

	hostUnit->SetState(State::E);

	//사용효과
	tick -= Time::DeltaTime();
}


void Skill_Garen_E::End()
{
	Skill::End();
	if (duration > 0.f) { // EE 로 빨리 취소했을때
		damageBuff->tick = damageBuff->duration;
		coolTime -= duration;
	}
}
