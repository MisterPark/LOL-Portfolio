#include "stdafx.h"
#include "Buff_Item_HealthPotion.h"
#include "Unit.h"

Buff_Item_HealthPotion::Buff_Item_HealthPotion(Unit* _host, float _duration, float _value) :Buff(_host, _duration)
{
	buffName = BuffName::Potion;
	healValue = _value;
}

Buff_Item_HealthPotion::~Buff_Item_HealthPotion()
{
	
}

void Buff_Item_HealthPotion::Update()
{
	tick += Time::DeltaTime();
	if (tick > 0.25f) {
		tick = 0.f;
		host->stat->IncreaseBaseValue(StatType::Health, healValue / duration * 4.f);

	}
}
