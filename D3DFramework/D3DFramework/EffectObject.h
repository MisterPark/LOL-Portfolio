#pragma once
#include "GameObject.h"

class EffectObject :
    public GameObject
{
public:
    EffectObject();
    virtual ~EffectObject();

    virtual void Initialize() override;
    virtual void Release() override;
    virtual void Update() override;

    void RotationBillboard();
    void ChaseTarget();
    void StickToTarget();

    void SetTarget(GameObject* _target);
    void SetOffset(Vector3 _offset);
    void SetDuration(float _duration);

private:
    float angle = 0.f;
protected:
    GameObject* target = nullptr;
    Vector3 offset;
    float tick = 0.f;
    float duration = INFINITY;
public:
    float speed = 1.f;
};

