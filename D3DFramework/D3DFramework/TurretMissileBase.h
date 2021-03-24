#pragma once
#include "GameObject.h"
class TurretMissileBase :
    public GameObject
{
public:
    TurretMissileBase();
    virtual~TurretMissileBase();
    virtual void Initialize() override;
    virtual void Release() override;
    virtual void Update() override;

public:
    Engine::Plane* mesh = nullptr;
};

