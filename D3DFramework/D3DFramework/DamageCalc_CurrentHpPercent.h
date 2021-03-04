#pragma once
#include "DamageCalc.h"
class DamageCalc_CurrentHpPercent :
    public DamageCalc
{
public:
    DamageCalc_CurrentHpPercent();
    ~DamageCalc_CurrentHpPercent();

    virtual void Calc(float* _damage, Stat* _myStat, Stat* _targetStat);

    static DamageCalc_CurrentHpPercent* CreateCalc(float _value, bool _trueDamage = false);

};

