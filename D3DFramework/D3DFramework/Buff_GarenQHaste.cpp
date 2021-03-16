#include "stdafx.h"
#include "Buff_GarenQHaste.h"
#include "Unit.h"

Buff_GarenQHaste::Buff_GarenQHaste(Unit* _host, float _duration) :Buff(_host,_duration)
{
	buffName = BuffName::GarenQHaste;
	AddModifier(StatType::MovementSpeed, 0.3f, true);
}

Buff_GarenQHaste::~Buff_GarenQHaste()
{
	host->moveState = State::RUN;
}

void Buff_GarenQHaste::Update()
{
	host->moveState = State::RUN2;
}
