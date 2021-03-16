#include "stdafx.h"
#include "Buff_GarenWReduction.h"
#include "Unit.h"

Buff_GarenWReduction::Buff_GarenWReduction(Unit* _host, float _duration, float _value) :Buff(_host, _duration)
{
	buffName = BuffName::GarenWReduction;
	AddModifier(StatType::DamageReduction, _value, false);
}

Buff_GarenWReduction::~Buff_GarenWReduction()
{
	
}

void Buff_GarenWReduction::Update()
{
	
}
