#pragma once
#include "GameObject.h"
#include "Unit.h"

class Missile :
    public GameObject
{
public:
    Missile();
    virtual ~Missile();
    // GameObject을(를) 통해 상속됨
    virtual void Initialize() override;
    virtual void Release() override;
    virtual void Update() override;

    void SetOwner(Unit* _owner);
    void SetTexture(const wstring& _key);
    void SetTarget(Unit* _target);


private:
    Unit* owner = nullptr;
    Engine::Plane* mesh = nullptr;

    Unit* attackTarget = nullptr;
    float movementSpeed = 5.f;

    float angle = 0.f;
};

