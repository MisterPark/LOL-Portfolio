#include "stdafx.h"
#include "Skill_MissFortune_E.h"
#include "Unit.h"
#include "PlayerController.h"
#include "Buff.h"
#include "DamageObject_MissFortune_E.h"
#include "DamageCalc_Basic.h"
#include "Buff_GarenEDamage.h"

Skill_MissFortune_E::Skill_MissFortune_E(Unit* _hostUnit)
{
	maxLevel = 5;
	coolTime = 7.f;
	coolTimeTick = coolTime;
	host = _hostUnit;
	range = 7.f;
	duration = 0.5f;
	level = 3;
}

Skill_MissFortune_E::~Skill_MissFortune_E()
{
}

void Skill_MissFortune_E::Use()
{
	PlayerController* controller = host->GetComponent<PlayerController>();
	controller->SetTargetMode(true);
	host->SetNextSkillReady(this);
}

bool Skill_MissFortune_E::InRange()
{
	return IsPositionInRange();
}

void Skill_MissFortune_E::Start()
{
	if (level == 0 || GetCooltime() > 0.f)
		return;

	Skill::Start();
	host->OnOtherSkillStart(this);

	DamageObject_MissFortune_E* damageObj = (DamageObject_MissFortune_E*)SceneManager::GetCurrentScene()->CreateObject<DamageObject_MissFortune_E>(Layer::Unit);
	float attackDamage = baseDamage + (level * growthDamage) + (host->stat->GetBaseValue(StatType::AbilityPower) * 0.8f);
	float attackInterval = 0.2f;
	damageObj->Set_DamageObject(host, this, host->attackPoint, 3.f , host->team, attackDamage * 0.1f, damageTime, attackInterval, -1.f, startTime);
	damageObj->SetSlowValue(baseSlow + level * growthSlow);
	//제일처음에 Basic만 잘 입혀줄것
	damageObj->Add_DamageCalc(DamageCalc_Basic::CreateCalc(DamageKind::AP));

	if (PlayerToDistanceCompare(host->GetTransform()->GetPos())) {
		SoundManager::GetInstance()->PlayOverlapSound(L"MissfortuneE1.ogg", SoundChannel::EFFECT);
	}

}

void Skill_MissFortune_E::Passive()
{
	if (coolTimeTick < coolTime)
	{
		coolTimeTick += Time::DeltaTime();
	}
}

void Skill_MissFortune_E::Active()
{
	if (tick >= duration) {
		End();
		return;
	}

	host->SetState(State::E);
	host->agent->Pause();

	//사용효과
	tick += Time::DeltaTime();
}


void Skill_MissFortune_E::End()
{
	Skill::End();
	host->agent->Resume();
}
