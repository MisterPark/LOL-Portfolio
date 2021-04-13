#include "stdafx.h"
#include "Buff_ItemWitchsFocus.h"

Buff_ItemWitchsFocus::Buff_ItemWitchsFocus(Unit* _host) : Buff(_host, INFINITY)
{
	buffName = BuffName::WitchsFocus;
	AddModifier(StatType::Armor, 0.f, false);
}

Buff_ItemWitchsFocus::~Buff_ItemWitchsFocus()
{
}

void Buff_ItemWitchsFocus::Update()
{
}
