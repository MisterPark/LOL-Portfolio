#include "stdafx.h"
#include "Buff_GarenWShield.h"
#include "Unit.h"

Buff_GarenWShield::Buff_GarenWShield(Unit* _host, float _duration, float _value) :Buff(_host, _duration)
{
	buffName = BuffName::GarenWShield;
	AddModifier(StatType::Shield, _value, false);
}

Buff_GarenWShield::~Buff_GarenWShield()
{

}

void Buff_GarenWShield::Update()
{

}
