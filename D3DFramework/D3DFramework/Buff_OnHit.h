#pragma once
#include "Buff.h"
#include "DamageCalc.h"
class Buff_OnHit :
    public Buff
{
public:
	Buff_OnHit(Unit* _host, float _duration, float _basicDamage, float _weightDamage, DamageKind _damageKind);
	virtual ~Buff_OnHit();

	virtual void Update();

public:
	float basicDamage = 0.f;
	float weightDamage = 0.f;
	DamageKind damageKind = DamageKind::END;
};

