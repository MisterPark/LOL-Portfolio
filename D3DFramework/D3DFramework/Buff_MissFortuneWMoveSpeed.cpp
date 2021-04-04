#include "stdafx.h"
#include "Buff_MissFortuneWMoveSpeed.h"
#include "Unit.h"
#include "Skill.h"

Buff_MissFortuneWMoveSpeed::Buff_MissFortuneWMoveSpeed(Unit* _host) :Buff(_host, INFINITY)
{
	buffName = BuffName::MissFortuneWMoveSpeed;
	AddModifier(StatType::MovementSpeed, 0.f, false);
}

Buff_MissFortuneWMoveSpeed::~Buff_MissFortuneWMoveSpeed()
{

}

void Buff_MissFortuneWMoveSpeed::Update()
{
	
}
