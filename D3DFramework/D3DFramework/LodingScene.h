#pragma once
#include "IScene.h"

using namespace PKH;

class LodingScene :
    public IScene
{
public:
    // IScene을(를) 통해 상속됨
    virtual void OnLoaded() override;
    virtual void OnUnloaded() override;
    virtual void Update() override;

    static void Count();
};

