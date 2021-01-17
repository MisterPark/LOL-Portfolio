#pragma once
#include "Unit.h"

class Monster : public EnemyUnit
{
public:
    Monster();
    virtual ~Monster();

    virtual void Initialize() override;
    virtual void Release() override;
    virtual void Update() override;

};
