#pragma once
#include "GameObject.h"
#include "Unit.h"

class Skill;
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

    void SetOwner(Unit* _owner, Skill* _ownerSkill);
    void SetTexture(const wstring& _key);
    void SetTarget(Unit* _target);


private:
    Unit* owner = nullptr;
    Skill* ownerSkill = nullptr;
    Engine::Plane* mesh = nullptr;

    Unit* attackTarget = nullptr;
    float movementSpeed = 10.f;

    float angle = 0.f;
};

