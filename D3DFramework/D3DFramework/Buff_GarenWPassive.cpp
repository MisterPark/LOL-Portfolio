#include "stdafx.h"
#include "Buff_GarenWPassive.h"
#include "Unit.h"

Buff_GarenWPassive::Buff_GarenWPassive(Unit* _host) :Buff(_host, INFINITY)
{
	buffName = BuffName::Buff_GarenWPassive;
	AddModifier(StatType::Armor, 0.f, false);
	AddModifier(StatType::MagicResistance, 0.f, false);
}

Buff_GarenWPassive::~Buff_GarenWPassive()
{

}

void Buff_GarenWPassive::Update()
{
	
}
