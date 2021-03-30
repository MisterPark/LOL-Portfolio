#include "stdafx.h"
#include "Buff_ItemDreadnought.h"
#include "Unit.h"
#include "Skill_Item_Dreadnought.h"

Buff_ItemDreadnought::Buff_ItemDreadnought(Unit* _host, Skill_Item_Dreadnought* _hostSkill, float _duration, float _basicDamage, float _weightDamage, DamageKind _damageKind) :Buff_OnHit(_host, _duration, _basicDamage, _weightDamage, _damageKind)
{
	buffName = BuffName::Dreadnought;
	maxOverlapCount = 100;
	overlapCount = 1;
	hostSkill = _hostSkill;
	AddModifier(StatType::MovementSpeed, 0.f, false);
}

Buff_ItemDreadnought::~Buff_ItemDreadnought()
{
	//hostSkill->buffDreadnought = nullptr;
}

void Buff_ItemDreadnought::Update()
{
	overlapCountStack += Time::DeltaTime() * 6.f;

	if (overlapCountStack > 1.f) {
		overlapCountStack -= 1.f;
		if(overlapCount < 100)
			overlapCount++;
	}

	basicDamage = (float)overlapCount;
	modifiers.front().value = (float)overlapCount * 0.006f;
}
