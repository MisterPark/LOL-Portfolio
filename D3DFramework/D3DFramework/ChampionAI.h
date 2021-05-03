#pragma once
#include "IComponent.h"

class Unit;

enum class Lane { BlueTop, BlueMid, BlueBot, RedTop, RedMid, RedBot, END };

class ChampionAI : public IComponent
{
public:
    explicit ChampionAI(GameObject* owner);
    explicit ChampionAI(const ChampionAI& rhs);
    virtual ~ChampionAI();

    virtual void Update() override;
    virtual IComponent* Clone() override;

    void SetLane(Lane _lane);

private:
    Unit* unit = nullptr;
    Unit* target = nullptr;

    bool startFlag = false;
    bool deadFlag = false;
    bool respawnFlag = false;

    list<Vector3> wayPoint;
    Vector3 nextPoint;
    float moveTick = 0.f;
    float moveDelay = 0.3f;

    float chaseTick = 0.f;
    float chaseDelay = 1.f;

    Lane lane = Lane::BlueTop;
    list<Vector3> wayPoints[MaxOfEnum<Lane>()];
};

