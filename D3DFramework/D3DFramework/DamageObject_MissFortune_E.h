#pragma once
#include "DamageObject.h"
class DamageObject_MissFortune_E :
    public DamageObject
{
public:
    DamageObject_MissFortune_E();
    ~DamageObject_MissFortune_E();


    virtual void Initialize() override;
    virtual void Release() override;
    virtual void Update() override;

    virtual void OnCollisionAddAttack(float damage, Collider* target) override;

    void SetSlowValue(float _value) { slowValue = _value; }
private:
    float slowValue = 0.f;
};

