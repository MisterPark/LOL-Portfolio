#include "stdafx.h"
#include "Buff_HealMoveSpeed.h"

Buff_HealMoveSpeed::Buff_HealMoveSpeed(Unit* _host) :Buff(_host, 1.f)
{
	buffName = BuffName::HealMoveSpeed;
	AddModifier(StatType::MovementSpeed, 0.3f, true);
}

Buff_HealMoveSpeed::~Buff_HealMoveSpeed()
{

}

void Buff_HealMoveSpeed::Update()
{
	
}
