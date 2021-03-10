#include "stdafx.h"
#include "Buff_OnHit.h"

Buff_OnHit::Buff_OnHit(Unit* _host, float _duration, float _basicDamage, float _weightDamage) :Buff(_host, _duration)
{
	basicDamage = _basicDamage;
	weightDamage = _weightDamage;
}

Buff_OnHit::~Buff_OnHit()
{
}

void Buff_OnHit::Update()
{
}
