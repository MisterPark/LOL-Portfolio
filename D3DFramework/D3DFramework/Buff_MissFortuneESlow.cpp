#include "stdafx.h"
#include "Buff_MissFortuneESlow.h"

Buff_MissFortuneESlow::Buff_MissFortuneESlow(Unit* _host, float _duration, float _value) :Buff(_host, _duration)
{
	buffName = BuffName::MissFortuneESlow;
	AddModifier(StatType::MovementSpeed, _value, true);
}

Buff_MissFortuneESlow::~Buff_MissFortuneESlow()
{

}

void Buff_MissFortuneESlow::Update()
{

}
