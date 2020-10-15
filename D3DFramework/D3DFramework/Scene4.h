#pragma once
#include "IScene.h"

using namespace PKH;

class Scene4 :
    public IScene
{
    // IScene을(를) 통해 상속됨
    virtual void OnLoaded() override;
    virtual void OnUnloaded() override;
    virtual void Update() override;

    float SceneStartTime;
    float MonsterRegenTime1;
    float MonsterRegenTime2;
    bool BossGen;
};

