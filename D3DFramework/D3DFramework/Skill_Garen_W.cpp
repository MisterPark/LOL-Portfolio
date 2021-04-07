#include "stdafx.h"
#include "Skill_Garen_W.h"
#include "Unit.h"
#include "Buff.h"
#include "Buff_GarenWReduction.h"
#include "Buff_GarenWShield.h"
#include "Buff_GarenWPassive.h"

Skill_Garen_W::Skill_Garen_W(Unit* _hostUnit)
{
	maxLevel = 5;
	coolTime = 2.f;
	coolTimeTick = coolTime;
	duration = 0.f;
	host = _hostUnit;
	level = 3;
}

Skill_Garen_W::~Skill_Garen_W()
{
}

void Skill_Garen_W::Start()
{
	if (level == 0 || GetCooltime() > 0.f)
		return;

	Skill::Start();
	host->OnOtherSkillStart(this);

	reductionTime = 1.25f + level * 0.75f;
	Buff_GarenWReduction* reductionBuff = new Buff_GarenWReduction(host, reductionTime, 0.5f);//reductionValue);
	host->stat->AddBuff(reductionBuff);

	//TODO : 가렌W 지금은 최대체력계수로 되어있지만 나중에 추가체력계수로 바꿔야함
	float shield = 70 + host->stat->GetValue(StatType::MaxHealth) * 0.2f;
	Buff_GarenWShield* attackBuff = new Buff_GarenWShield(host, 0.75f, shield);
	host->stat->AddBuff(attackBuff);


}

void Skill_Garen_W::Passive()
{
	if (coolTimeTick < coolTime)
	{
		coolTimeTick += Time::DeltaTime();
	}

	if (level == 0)
		return;
	
	

	if (passiveBuff == nullptr) {
		passiveBuff = new Buff_GarenWPassive(host);
		host->stat->AddBuff(passiveBuff);
	}
	passiveBuff->modifiers.front().value = passiveStack * 0.25f;
	passiveBuff->modifiers.back().value = passiveStack * 0.25f;

}

void Skill_Garen_W::Active()
{
	End();
}


void Skill_Garen_W::End()
{
	Skill::End();
}

void Skill_Garen_W::OnKilled(Unit* target)
{
	passiveStack++;
}
