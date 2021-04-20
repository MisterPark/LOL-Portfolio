#pragma once
#include "IComponent.h"

class Unit;

class ChampionAI : public IComponent
{
public:
    explicit ChampionAI(GameObject* owner);
    explicit ChampionAI(const ChampionAI& rhs);
    virtual ~ChampionAI();

    virtual void Update() override;
    virtual IComponent* Clone() override;

private:
    Unit* unit = nullptr;

    bool startFlag = false;
    bool deadFlag = false;
    bool respawnFlag = false;

    list<Vector3> wayPoint;
    Vector3 nextPoint;
    float moveTick = 0.f;
    float moveDelay = 0.3f;
};

