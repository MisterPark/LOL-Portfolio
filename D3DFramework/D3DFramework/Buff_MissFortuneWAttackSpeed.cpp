#include "stdafx.h"
#include "Buff_MissFortuneWAttackSpeed.h"


Buff_MissFortuneWAttackSpeed::Buff_MissFortuneWAttackSpeed(Unit* _host, float _duration, float _value) :Buff(_host, _duration)
{
	buffName = BuffName::MissFortuneWAttackSpeed;
	AddModifier(StatType::AttackSpeed, _value, true);
}

Buff_MissFortuneWAttackSpeed::~Buff_MissFortuneWAttackSpeed()
{
	
}

void Buff_MissFortuneWAttackSpeed::Update()
{
	
}
