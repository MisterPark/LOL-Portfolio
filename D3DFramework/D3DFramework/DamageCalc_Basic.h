#pragma once
#include "DamageCalc.h"

class DamageCalc_Basic :
    public DamageCalc
{
public:
    DamageCalc_Basic();
    ~DamageCalc_Basic();

    virtual void Calc(float* _damage, UnitStat* _myStat, UnitStat* _targetStat);

    static DamageCalc_Basic* CreateCalc(float _value = 0.f, bool _trueDamage = false);

};

