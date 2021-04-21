#pragma once
#include "Unit.h"

class TurretFloatingBar;

class Building :
    public Unit
{
public:
    Building();
    virtual ~Building();

    virtual void OnCollisionEnter(Collider* target);
    //virtual void Chase(Vector3 _target);

    virtual void OnDamaged(Unit* target, Skill* targetSkill, float* damage) override;
    
public:
    list<Building*> frontBuildingList;
};

