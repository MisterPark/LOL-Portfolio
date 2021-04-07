#pragma once
#include "Scene.h"
#include "Unit.h"
using namespace Engine;

class Label;

class TestScene2 :
    public Scene
{
public:
    virtual void OnLoaded() override;
    virtual void OnUnloaded() override;
    virtual void Update() override;

    void SpawnMinion();

    void CreateEnvironment();
    void CreateBuilding();
    void CreateMonster();

    void CreateMinionCaster();
    void CreateMinionMelee();
    void CreateMinionSiege();
    void CreateMinionSuper();
    
    Label* testLabel = nullptr;
    map<INT, Unit*> unitMap;
    int unitID = (int)UnitID::END;
};

