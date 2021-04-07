#include "stdafx.h"
#include "Buff_ItemSpellBlade.h"

Buff_ItemSpellBlade::Buff_ItemSpellBlade(Unit* _host, float _duration, float _basicDamage, DamageKind _damageKind) : Buff_OnHit(host, _duration, _basicDamage, 0.f, _damageKind)
{

}

Buff_ItemSpellBlade::~Buff_ItemSpellBlade()
{
}

void Buff_ItemSpellBlade::Update()
{
}
