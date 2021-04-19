#include "stdafx.h"
#include "Buff_Item_WraithStep.h"
#include "Unit.h"
#include "Skill.h"

Buff_Item_WraithStep::Buff_Item_WraithStep(Unit* _host, float _duration, float _value) :Buff(_host, _duration)
{
	buffName = BuffName::WraithStep;
	AddModifier(StatType::MovementSpeed, _value, true);
}

Buff_Item_WraithStep::~Buff_Item_WraithStep()
{

}

void Buff_Item_WraithStep::Update()
{

}