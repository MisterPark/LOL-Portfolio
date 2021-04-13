#include "stdafx.h"
#include "Buff_Item_Nimble.h"

Buff_ItemNimble::Buff_ItemNimble(Unit* _host, float _duration, float _value) :Buff(_host, _duration)
{
	buffName = BuffName::Nimble;
	AddModifier(StatType::MovementSpeed, _value, false);
}

Buff_ItemNimble::~Buff_ItemNimble()
{
}

void Buff_ItemNimble::Update()
{
}
