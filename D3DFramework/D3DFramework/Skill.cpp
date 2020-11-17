#include "stdafx.h"
#include "Skill.h"
#include "Character.h"

Skill::Skill() :
	character(nullptr), coolTime(0.f), maxCoolTime(0.f),
	activeTime(0.f), moveStopTime(0.f),
	isCoolDownNow(false), isActive(false), canMove(false)
{
	SkillManager::GetInstance()->AddSkillToList(this);
}

Skill::~Skill()
{
	SkillManager::GetInstance()->DeleteSkillFromList(this);
}

bool Skill::Active(Character * _character)
{
	// 쿨다운 중이 아니고 액티브 중이 아닐 때
	if (!isCoolDownNow && !isActive)
	{
		character = _character;
		isActive = true;
		InitActiveTime();

		isCoolDownNow = true;
		InitCoolTime();

		return true;
	}
	return false;
}

void Skill::CalcActiveTime()
{
	if (isActive)
	{
		activeTime -= TimeManager::DeltaTime();
		if (0.f > activeTime)SetNoneActive();
	}
}

void Skill::CalcCoolTime()
{
	if (isCoolDownNow)
	{
		coolTime -= TimeManager::DeltaTime();

		if (0.f > coolTime)
		{
			isCoolDownNow = false;
			InitCoolTime();
		}
	}
}


void Skill::SetNoneActive()
{
	InitActiveTime();
	isActive = false;
}

TextureKey Skill::GetSkillIcon()
{
	return skillIcon;
}

float Skill::GetCoolTime()
{
	return coolTime;
}

float Skill::GetMaxCoolTime()
{
	return maxCoolTime;
}

float Skill::GetActiveTime()
{
	return activeTime;
}

float Skill::GetMoveStopTime()
{
	return moveStopTime;
}

bool Skill::GetIsCoolDown()
{
	return isCoolDownNow;
}

bool Skill::GetIsActive()
{
	return isActive;
}

bool Skill::GetCanMove()
{
	return canMove;
}
