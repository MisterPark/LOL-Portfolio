#pragma once
#include "DamageCalc.h"
class DamageCalc_Critical :
    public DamageCalc
{
public:
    DamageCalc_Critical();
    ~DamageCalc_Critical();

    virtual void Calc(float* _damage, Stat* _myStat, Stat* _targetStat);

    static DamageCalc_Critical* CreateCalc();

};

