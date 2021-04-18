#include "stdafx.h"
#include "Buff_Item_SteelTipped.h"

Buff_Item_SteelTipped::Buff_Item_SteelTipped(Unit* _host, float _basicDamage, DamageKind _damageKind) :Buff_OnHit(_host, INFINITY, _basicDamage, 0.f, _damageKind)
{
	buffName = BuffName::SteelTipped;
}

Buff_Item_SteelTipped::~Buff_Item_SteelTipped()
{
}

void Buff_Item_SteelTipped::Update()
{

}
