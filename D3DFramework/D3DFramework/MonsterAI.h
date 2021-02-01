#pragma once
#include "IComponent.h"

class Unit;

class MonsterAI : public IComponent
{
public:
    explicit MonsterAI(GameObject* owner);
    explicit MonsterAI(const MonsterAI& rhs);
    virtual ~MonsterAI();

    virtual void Update() override;
    virtual IComponent* Clone() override;

    void SetTarget(Unit* _target);

private:
    Unit* unit = nullptr;
    Unit* target = nullptr;
};

