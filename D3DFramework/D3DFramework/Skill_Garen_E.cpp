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
	maxLevel = 5;
	coolTime_Init = 9.f;
	duration = 3.f;
	hostUnit = _hostUnit;
}

Skill_Garen_E::~Skill_Garen_E()
{
}

void Skill_Garen_E::Start()
{
	if (duration > 0.f)
		tick = 0;
	if (coolTime > 0.f)
		return;

	Skill::Start();

	DamageObject_Garen_E* damageObj = (DamageObject_Garen_E*)SceneManager::GetCurrentScene()->CreateObject<DamageObject_Garen_E>(Layer::Unit);
	float attackDamage = (4.f * level) + hostUnit->stat->GetValue(StatType::AttackDamage) * (0.3f + level * 0.02f);
	float attackInterval = 3.f / 7.f;// + TODO: 아이템과 레벨업으로 인한 추가공격횟수 추가해줘야함
	damageObj->Set_DamageObject(hostUnit, hostUnit->transform->GetPos(), 3.25f, hostUnit->team, attackDamage, duration, attackInterval);
	damageObj->Set_ObjectFollow(hostUnit);
	//제일처음에 Basic만 잘 입혀줄것
	damageObj->Add_DamageCalc(DamageCalc_Basic::CreateCalc(DamageKind::AD));

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
		coolTime -= duration;
		damageBuff->tick = damageBuff->duration;
	}
}
