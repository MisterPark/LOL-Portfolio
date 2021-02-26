#pragma once
#include "IComponent.h"
#include "IComponent.h"
#include "NavMeshAgent.h"

using namespace Engine;

class Unit;

class NetPlayerController :
    public IComponent
{
public:
    explicit NetPlayerController(GameObject* owner);
    explicit NetPlayerController(const NetPlayerController& rhs);
    virtual ~NetPlayerController();

    virtual void Update() override;
    // IComponent을(를) 통해 상속됨
    virtual IComponent* Clone() override;

    void SetTargetMode(bool _mode);

    void ReqMove(Vector3 _dest, bool _noSearch = false);
    void ReqAttack(Unit* _target);

public:
    Network* net = nullptr;
    Engine::NavMeshAgent* agent = nullptr;
    bool targetMode = false;
    Unit* unit = nullptr;
};

