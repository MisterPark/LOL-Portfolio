#pragma once
#include "IScene.h"
class Scene03 :
    public IScene
{
    // IScene을(를) 통해 상속됨
    virtual void OnLoaded() override;
    virtual void OnUnloaded() override;
    virtual void Update() override;
    float tick = 0.f;

    float fdust = 0.f;
    int MonsterMakeCount = 0;
    int BossmakeCount = 0;



    float EndCount = 0;

    bool GameEnd = false;
};

