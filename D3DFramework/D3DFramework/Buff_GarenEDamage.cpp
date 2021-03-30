#include "stdafx.h"
#include "Buff_GarenEDamage.h"
#include "Unit.h"

Buff_GarenEDamage::Buff_GarenEDamage(Unit* _host, float _duration, DamageObject_Garen_E* _damageObject) :Buff(_host, _duration)
{
	buffName = BuffName::GarenEDamage;
	damageObject = _damageObject;
}

Buff_GarenEDamage::~Buff_GarenEDamage()
{
	duration;
	tick;
	if (damageObject != nullptr)
		damageObject->Set_Dead();
	
}

void Buff_GarenEDamage::Update()
{
	
}
