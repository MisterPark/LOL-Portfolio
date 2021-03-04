#include "stdafx.h"
#include "Skill_Garen_Q.h"
#include "Unit.h"

Skill_Garen_Q::Skill_Garen_Q()
{
	coolTime_Init = 8.f;
	duration = 4.5f;
}

Skill_Garen_Q::~Skill_Garen_Q()
{
}

void Skill_Garen_Q::Start()
{
	addSpeedValue = hostUnit->stat->GetValue(StatType::MovementSpeed) * (addSpeedPercent * 0.01f);
	// TODO : 버프로 넣어야함
	//hostUnit->stat->movementSpeed.AddModifier(addSpeedValue);
	durationSpeedTime = 0.35f + level * 0.65f;
}

void Skill_Garen_Q::Update()
{
	if (coolTime > 0.f) {
		coolTime -= Time::DeltaTime();
	}
	//if (!hostUnit->skill어떤거돌고잇는지체크)
//		return;
	if(duration <= 0.f){
		End();
		return;
	}

	duration -= Time::DeltaTime();
	if (durationSpeedTime > 0.f) {
		durationSpeedTime -= Time::DeltaTime();
	}
	else if (durationSpeedTime != -1.f) {
		//hostUnit->stat->movementSpeed.RemoveModifier(addSpeedValue);
		durationSpeedTime = -1.f;
	}

}

void Skill_Garen_Q::End()
{
	
}
