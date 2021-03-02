#pragma once
#include "Scene.h"

using namespace Engine;

class Label;

class TestScene :
    public Scene
{
    // Scene을(를) 통해 상속됨
    virtual void OnLoaded() override;
    virtual void OnUnloaded() override;
    virtual void Update() override;

    void CreateMinionCaster();

public:
    Label* testLabel = nullptr;
    Unit* testUnit = nullptr;
};
