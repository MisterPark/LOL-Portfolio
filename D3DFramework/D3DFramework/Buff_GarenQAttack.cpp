#include "stdafx.h"
#include "Buff_GarenQAttack.h"
#include "Unit.h"

Buff_GarenQAttack::Buff_GarenQAttack(Unit* _host, float _duration) :Buff(_host, _duration)
{
}

Buff_GarenQAttack::~Buff_GarenQAttack()
{
	host->attackState = State::ATTACK1;
}

void Buff_GarenQAttack::Update()
{
	host->attackState = State::Q;
}
