#pragma once
#include "DamageCalc.h"
class DamageCalc_OnHit :
    public DamageCalc
{
private:
    DamageCalc_OnHit();
public:
    ~DamageCalc_OnHit();

    virtual void Calc(float* _damage, Stat* _myStat, Stat* _targetStat);

    static DamageCalc_OnHit* CreateCalc(DamageKind _damageKind);
};

