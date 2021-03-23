#pragma once
#include "IComponent.h"
#include "NavMeshAgent.h"

using namespace Engine;

class Unit;
class TargetingSkill;

class PlayerController :
    public IComponent
{
public:
    explicit PlayerController(GameObject* owner);
    explicit PlayerController(const PlayerController& rhs);
    virtual ~PlayerController();

    virtual void Update() override;
    // IComponent을(를) 통해 상속됨
    virtual IComponent* Clone() override;

    void SetTargetMode(bool _mode);
    void SetTargetingSkill(TargetingSkill* _targetingSkill);

public:
    Engine::NavMeshAgent* agent = nullptr;
    Unit* unit = nullptr;
    
    bool targetMode = false;
    TargetingSkill* targetingSkill = nullptr;
};

