#include "stdafx.h"
#include "Buff_ItemWraithStep.h"
#include "Unit.h"
#include "Skill.h"

Buff_ItemWraithStep::Buff_ItemWraithStep(Unit* _host, float _duration, float _value) :Buff(_host, _duration)
{
	buffName = BuffName::WraithStep;
	AddModifier(StatType::MovementSpeed, _value, true);
}

Buff_ItemWraithStep::~Buff_ItemWraithStep()
{

}

void Buff_ItemWraithStep::Update()
{

}