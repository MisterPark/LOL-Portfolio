#include "stdafx.h"
#include "Buff_GarenPHealthRegen.h"
#include "Unit.h"

Buff_GarenPHealthRegen::Buff_GarenPHealthRegen(Unit* _host, float _duration) :Buff(_host, _duration)
{
	buffName = BuffName::GarenPHealthRegen;
	AddModifier(StatType::HealthRegen, 0.f, false);
}

Buff_GarenPHealthRegen::~Buff_GarenPHealthRegen()
{

}
	
void Buff_GarenPHealthRegen::Update()
{
	float test = host->stat->GetValue(StatType::MaxHealth) * 0.1f;
	modifiers.front().value = host->stat->GetValue(StatType::MaxHealth) * 0.1f;// 0.015f;
}