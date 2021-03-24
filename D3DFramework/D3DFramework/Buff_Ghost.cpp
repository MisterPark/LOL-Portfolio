#include "stdafx.h"
#include "Buff_Ghost.h"
#include "Unit.h"

Buff_Ghost::Buff_Ghost(Unit* _host, float _duration, float _value) :Buff(_host, _duration)
{
	buffName = BuffName::Ghost;
	AddModifier(StatType::MovementSpeed, 0.f, true);
	movementSpeed_Init = _value;
	maxOverlapCount = 5;
}

Buff_Ghost::~Buff_Ghost()
{
	
}

void Buff_Ghost::Update()
{
	modifiers.front().value = movementSpeed_Init * 0.5f * (float)(overlapCount + 1);
}
