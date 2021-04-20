#pragma once
#include "Unit.h"
class Building :
    public Unit
{
public:
    Building();
    virtual ~Building();

    virtual void OnCollisionEnter(Collider* target);
    //virtual void Chase(Vector3 _target);

    virtual void OnDamaged(Unit* target, Skill* targetSkill, float* damage) override;
    list<Building*> frontBuildingList;
};

