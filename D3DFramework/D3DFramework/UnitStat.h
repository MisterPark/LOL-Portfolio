#pragma once
#include "IComponent.h"
#include "Stat.h"

class UnitStat :
    public IComponent
{
public:
    explicit UnitStat(GameObject* owner);
    explicit UnitStat(const UnitStat& rhs);
    virtual ~UnitStat();
    virtual IComponent* Clone() override;


public:
	Stat attackDamage = 15.f;
	Stat abilityPower = 0.f;
	Stat adPenetrate = 0.f;
	Stat adPenetratePercent = 0.f;
	Stat apPenetrate = 0.f;
	Stat apPenetratePercent = 0.f;
	Stat armor = 1;
	Stat magicResistance = 1.f;
	Stat movementSpeed = 3.5f;
	Stat criticalPer = 0.f;
	Stat cooldownReduction = 0.f;

	Stat hp = 100.f;
	Stat maxHp = 100.f;
	Stat mp = 100.f;
	Stat maxMp = 100.f;
	Stat exp = 0.f;
	Stat maxExp = 100.f;
	int level = 1;

	// 5초당
	Stat hpRegen = 1.f;
	// 5초당
	Stat mpRegen = 1.f;
};

