#pragma once
#include "IComponent.h"

class Unit;

class MinionAI :
    public IComponent
{
public:
    explicit MinionAI(GameObject* owner);
    explicit MinionAI(const MinionAI& rhs);
    virtual ~MinionAI();

    virtual void Update() override;
    virtual IComponent* Clone() override;

    void SetTarget(Unit* _target);

public:
    list<Vector3> wayPoint;
    Vector3 nextPoint;
private:
    Network* net = nullptr;
    Unit* unit = nullptr;
    Unit* target = nullptr;
    float moveTick = 0.f;
    float moveDelay = 0.3f;
};

