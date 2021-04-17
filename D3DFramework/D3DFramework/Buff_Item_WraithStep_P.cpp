#include "stdafx.h"
#include "Buff_Item_WraithStep_P.h"
#include "Unit.h"
#include "Skill.h"

Buff_Item_WraithStep_P::Buff_Item_WraithStep_P(Unit* _host) :Buff(_host, INFINITY)
{
	buffName = BuffName::WraithStep_P;
	AddModifier(StatType::MovementSpeed, 0.f, false);
}

Buff_Item_WraithStep_P::~Buff_Item_WraithStep_P()
{

}

void Buff_Item_WraithStep_P::Update()
{

}