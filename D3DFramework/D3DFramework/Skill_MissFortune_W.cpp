#include "stdafx.h"
#include "Skill_MissFortune_W.h"
#include "Buff_MissFortuneWAttackSpeed.h"
#include "Buff_MissFortuneWMoveSpeed.h"
#include "Unit.h"

Skill_MissFortune_W::Skill_MissFortune_W(Unit* _hostUnit)
{
	maxLevel = 5;
	coolTime = 2.f;
	coolTimeTick = coolTime;
	duration = 0.f;
	host = _hostUnit;
	level = 3;
}

Skill_MissFortune_W::~Skill_MissFortune_W()
{
}

void Skill_MissFortune_W::Start()
{
	if (level == 0 || GetCooltime() > 0.f)
		return;

	Skill::Start();
	host->OnOtherSkillStart(this);

	float attackSpeedValue = activeAttackSpeed + activeAttackSpeedGrowth * host->stat->GetBaseValue(StatType::Level);
	Buff_MissFortuneWAttackSpeed* attackSpeedBuff = new Buff_MissFortuneWAttackSpeed(host, activeAttackSpeedTime, attackSpeedValue);//reductionValue);
	host->stat->AddBuff(attackSpeedBuff);

	passiveTick = 10.f;
}

void Skill_MissFortune_W::Passive()
{
	if (level == 0)
		return;

	if (coolTimeTick < coolTime)
	{
		coolTimeTick += Time::DeltaTime();
	}
	passiveTick += Time::DeltaTime();

	if (moveSpeedBuff == nullptr) {
		moveSpeedBuff = new Buff_MissFortuneWMoveSpeed(host);
		host->stat->AddBuff(moveSpeedBuff);
	}

	if (passiveTick > 10.f)
		moveSpeedBuff->modifiers.front().value = movementMaxSpeed + host->skillList[(int)SkillIndex::W]->GetLevel() * 0.1f;
	else if (passiveTick > 5.f)
		moveSpeedBuff->modifiers.front().value = 0.25f;
	else
		moveSpeedBuff->modifiers.front().value = 0.f;
}

void Skill_MissFortune_W::Active()
{
	End();
}


void Skill_MissFortune_W::End()
{
	Skill::End();
}

void Skill_MissFortune_W::OnDamaged(Unit* target, Skill* targetSkill, float* damage)
{
	passiveTick = 0.f;
}
