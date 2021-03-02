#pragma once
#include "DamageCalc.h"

class DamageCalc_LostHpPercent :
    public DamageCalc
{
public:
    DamageCalc_LostHpPercent();
    ~DamageCalc_LostHpPercent();

    virtual void Calc(float* _damage, UnitStat* _myStat, UnitStat* _targetStat);

    static DamageCalc_LostHpPercent* CreateCalc(float _value, bool _trueDamage = false);

};

