#pragma once
#include "Scene.h"
#include "Unit.h"

using namespace Engine;

class Label;

class TestScene :
    public Scene
{
public:
    // Scene을(를) 통해 상속됨
    virtual void OnLoaded() override;
    virtual void OnUnloaded() override;
    virtual void Update() override;

    void Progress();

    void CreateEnvironment();
    void CreateBuilding();
    void CreateMonster();


public:
    Label* testLabel = nullptr;
    Unit* testUnit = nullptr;

    map<INT, Unit*> unitMap;
    int unitID = (int)UnitID::END;

};
