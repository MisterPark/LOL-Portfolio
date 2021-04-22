﻿#include "stdafx.h"
#include "Skill_Garen_R.h"
#include "Buff.h"
#include "Collider.h"
#include "SphereCollider.h"
#include "Unit.h"
#include "DamageCalc_Basic.h"
#include "DamageCalc_LostHpPercent.h"
#include "Champion.h"
#include "Effect_Garen_R_SwordMove.h"
#include "Effect_Garen_R_SwordFixed.h"
#include "Effect_Garen_R_GroundDecal.h"
#include "Effect_Garen_R_GroundImpact.h"
#include "Effect_Garen_R_Dome.h"

Skill_Garen_R::Skill_Garen_R(Unit* _hostUnit)
{
	groundClick = false;

	maxLevel = 3;
	coolTime = 2.f;
	coolTimeTick = coolTime;
	duration = 1.f;
	host = _hostUnit;
	range = 4.f;

	Add_DamageCalc(DamageCalc_Basic::CreateCalc(DamageKind::TrueDamage));
	Add_DamageCalc(DamageCalc_LostHpPercent::CreateCalc(0.1f, DamageKind::TrueDamage));
}

Skill_Garen_R::~Skill_Garen_R()
{
}

void Skill_Garen_R::Start()
{
	if (level == 0 || GetCooltime() > 0.f)
		return;


	Skill::Start();
	host->OnOtherSkillStart(this);

	if (1)
	{
		Effect_Garen_R_SwordMove* effMove = (Effect_Garen_R_SwordMove*)SceneManager::GetCurrentScene()->CreateObject<Effect_Garen_R_SwordMove>(Layer::Effect);
		effMove->SetTarget(host->attackTarget);
		effMove->SetDuration(2.f);
	}

	if (1)
	{
		Effect_Garen_R_SwordFixed* effFixed = (Effect_Garen_R_SwordFixed*)SceneManager::GetCurrentScene()->CreateObject<Effect_Garen_R_SwordFixed>(Layer::Effect);
		effFixed->SetTarget(host->attackTarget);
		effFixed->SetDuration(1.5f);
	}

	if (1)
	{
		Effect_Garen_R_GroundDecal* effGround = (Effect_Garen_R_GroundDecal*)SceneManager::GetCurrentScene()->CreateObject<Effect_Garen_R_GroundDecal>(Layer::Effect);
		effGround->SetTarget(host->attackTarget);
		effGround->SetDuration(2.5f);
	}

	if (1)
	{
		Effect_Garen_R_GroundImpact* effGroundImpact = (Effect_Garen_R_GroundImpact*)SceneManager::GetCurrentScene()->CreateObject<Effect_Garen_R_GroundImpact>(Layer::Effect);
		effGroundImpact->SetTarget(host->attackTarget);
		effGroundImpact->SetDuration(1.1f);
	}

	if (1)
	{
		Effect_Garen_R_Dome* effDome = (Effect_Garen_R_Dome*)SceneManager::GetCurrentScene()->CreateObject<Effect_Garen_R_Dome>(Layer::Effect);
		effDome->SetTarget(host->attackTarget);
		effDome->SetDuration(1.1f);
	}

	Ray ray = Camera::main->ScreenPointToRay(Input::GetMousePosition());


	Calc_TakeDamege(baseDamage);



}

void Skill_Garen_R::Passive()
{
	if (coolTimeTick < coolTime)
	{
		coolTimeTick += Time::DeltaTime();
	}

}

void Skill_Garen_R::Active()
{
	//if (!active)
		//return;

	if (tick > duration) {
		End();
		return;
	}

	host->agent->Stop();
	host->SetState(State::R);
	//사용효과
	tick += Time::DeltaTime();
}


void Skill_Garen_R::End()
{
	Skill::End();
	host->SetAttackTarget(nullptr);
}

bool Skill_Garen_R::TargetingSuccess(Unit* target)
{
	//
	//if (target == host)
		//return false;
	//TODO::나중에 챔피언만으로 바꿀예정
	if (target->team != host->team)
		return true;
	return false;
}

