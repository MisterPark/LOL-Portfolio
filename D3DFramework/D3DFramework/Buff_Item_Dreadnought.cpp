#include "stdafx.h"
#include "Buff_Item_Dreadnought.h"
#include "Unit.h"
#include "Skill_Item_Dreadnought.h"

Buff_ItemDreadnought::Buff_ItemDreadnought(Unit* _host, Skill_Item_Dreadnought* _hostSkill, float _duration, float _basicDamage, float _weightDamage, DamageKind _damageKind) :Buff_OnHit(_host, _duration, _basicDamage, _weightDamage, _damageKind)
{
	buffName = BuffName::Dreadnought;
	maxOverlapCount = 6;
	overlapCount = 1;
	AddModifier(StatType::MovementSpeed, 0.f, false);
}

Buff_ItemDreadnought::~Buff_ItemDreadnought()
{

}

void Buff_ItemDreadnought::Update()
{
	skillTick += Time::DeltaTime() * 6.f;

	if (skillTick > 1.f) {
		skillTick -= 1.f;
		if(skillStack < 100)
			skillStack++;
	}

	basicDamage = skillStack;
	modifiers.front().value = skillStack * 0.006f;
}
