#pragma once
#include "DamageObject.h"
class DamageObject_Garen_E :
    public DamageObject
{
public:
    DamageObject_Garen_E();
    ~DamageObject_Garen_E();


    virtual void Initialize() override;
    virtual void Release() override;
    virtual void Update() override;

    virtual void OnCollisionEnter(Collider* target);

    void TakeDamage();
    void Set_Dead() { isDead = true; };
private:
    list<Unit*> damageExpected;
    Unit* proximateUnit = nullptr;
    bool isDead = false;
};

