#pragma once
#include "IComponent.h"

class Unit;

class ScuttleracerAI :
    public IComponent
{
public:
    explicit ScuttleracerAI(GameObject* owner);
    explicit ScuttleracerAI(const ScuttleracerAI& rhs);
    virtual ~ScuttleracerAI();

    virtual void Update() override;
    virtual IComponent* Clone() override;

public:
    Unit* unit = nullptr;
    list<Vector3> wayPoint;
    Vector3 nextPoint;
    float moveTick = 0.f;
    float moveDelay = 0.3f;
};

