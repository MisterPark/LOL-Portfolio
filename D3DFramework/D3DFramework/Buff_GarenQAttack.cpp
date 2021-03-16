#include "stdafx.h"
#include "Buff_GarenQAttack.h"
#include "Unit.h"

Buff_GarenQAttack::Buff_GarenQAttack(Unit* _host, float _duration, float _basicDamage, float _weightDamage) :Buff_OnHit(_host, _duration, _basicDamage, _weightDamage)
{
	buffName = BuffName::GarenQAttack;
}

Buff_GarenQAttack::~Buff_GarenQAttack()
{
	host->attackState = State::ATTACK1;
}

void Buff_GarenQAttack::Update()
{
	host->attackState = State::Q;

}
