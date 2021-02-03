#pragma once
#include "GameObject.h"
#include "Animation.h"

class TurretBreak :
    public GameObject
{
public:
    TurretBreak();
    virtual ~TurretBreak();

    virtual void Initialize() override;
    virtual void Release() override;
    virtual void Update() override;
    virtual void PostUpdate() override;


public:
    Animation* anim1 = nullptr;
    Animation* anim2 = nullptr;
    Animation* anim3 = nullptr;
    DynamicMesh* mesh1 = nullptr;
    DynamicMesh* mesh2 = nullptr;
    DynamicMesh* mesh3 = nullptr;

    bool ats = false;
};

