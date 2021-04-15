#include "stdafx.h"
#include "Buff_Item_ManaCharge.h"

Buff_ItemManaCharge::Buff_ItemManaCharge(Unit* _host) : Buff(_host, INFINITY)
{
	buffName = BuffName::ManaCharge;
	AddModifier(StatType::MaxMana, 0.f, false);
}

Buff_ItemManaCharge::~Buff_ItemManaCharge()
{
}

void Buff_ItemManaCharge::Update()
{
}
