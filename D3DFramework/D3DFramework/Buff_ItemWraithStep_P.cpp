#include "stdafx.h"
#include "Buff_ItemWraithStep_P.h"
#include "Unit.h"
#include "Skill.h"

Buff_ItemWraithStep_P::Buff_ItemWraithStep_P(Unit* _host) :Buff(_host, INFINITY)
{
	buffName = BuffName::WraithStep_P;
	AddModifier(StatType::MovementSpeed, 0.f, false);
}

Buff_ItemWraithStep_P::~Buff_ItemWraithStep_P()
{

}

void Buff_ItemWraithStep_P::Update()
{

}