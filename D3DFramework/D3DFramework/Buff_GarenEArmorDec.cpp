#include "stdafx.h"
#include "Buff_GarenEArmorDec.h"
#include "Unit.h"

Buff_GarenEArmorDec::Buff_GarenEArmorDec(Unit* _host, float _duration) :Buff(_host, _duration)
{
	buffName = BuffName::GarenEArmorDec;
	AddModifier(StatType::Armor, 0.f, true);
	maxOverlapCount = 6;
}

Buff_GarenEArmorDec::~Buff_GarenEArmorDec()
{

}

void Buff_GarenEArmorDec::Update()
{
	if(overlapCount == maxOverlapCount)
		modifiers.front().value = -0.25f;
	else
		modifiers.front().value = 0.f;
}
