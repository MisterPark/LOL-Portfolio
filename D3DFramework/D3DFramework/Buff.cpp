#include "stdafx.h"
#include "Buff.h"

Buff::Buff(float _value, float _duration)
{
	this->baseValue = _value;
	this->duration = _duration;
	this->tick = 0.f;
}

bool Buff::Update()
{
	tick += Time::DeltaTime();
	if (tick >= duration)
	{
		return false;
	}

	return true;
}
