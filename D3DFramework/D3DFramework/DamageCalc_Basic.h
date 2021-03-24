#pragma once
#include "DamageCalc.h"

class DamageCalc_Basic :
    public DamageCalc
{
public:
    DamageCalc_Basic();
    ~DamageCalc_Basic();

    virtual void Calc(float* _damage, Stat* _myStat, Stat* _targetStat);

    static DamageCalc_Basic* CreateCalc(DamageKind _damageKind);

};

