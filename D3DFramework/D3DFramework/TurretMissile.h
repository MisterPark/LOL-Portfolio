#pragma once
#include "Unit.h"
#include "Rectangle.h"

using namespace PKH;

class TurretMissile : public GameObject
{
public:
    TurretMissile();
    virtual ~TurretMissile();
    virtual void Initialize() override;
    virtual void Release() override;

    virtual void Update() override;

    void SetTeam(Team _team);
    void SetAttackTarget(Unit* _target);

private:
    PKH::Rectangle* mesh = nullptr;

    Team team = Team::NEUTRAL;
    Unit* attackTarget = nullptr;
    float movementSpeed = 5.f;
    float attackDamage = 1.f;
   

    
};

