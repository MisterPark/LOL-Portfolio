#pragma once
#include "IScene.h"

class Label;
class ProgressBar;

class LoadingScene :
    public IScene
{
public:
    // IScene을(를) 통해 상속됨
    virtual void OnLoaded() override;
    virtual void OnUnloaded() override;
    virtual void Update() override;


    Label* label = nullptr;
    ProgressBar* bar = nullptr;

};

