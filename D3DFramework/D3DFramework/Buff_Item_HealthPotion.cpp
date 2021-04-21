#include "stdafx.h"
#include "Buff_Item_HealthPotion.h"
#include "Unit.h"

Buff_Item_HealthPotion::Buff_Item_HealthPotion(Unit* _host, float _duration, float _value) :Buff(_host, _duration)
{
	buffName = BuffName::Potion;
	AddModifier(StatType::HealthRegen, _value / _duration, false);
}

Buff_Item_HealthPotion::~Buff_Item_HealthPotion()
{
	
}

void Buff_Item_HealthPotion::Update()
{

}
