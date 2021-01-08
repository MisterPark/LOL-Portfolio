#pragma once
#include "IScene.h"

class LoadingChampScreen;

class TestLoadingScene :
    public IScene
{
    // IScene을(를) 통해 상속됨
    virtual void OnLoaded() override;
    virtual void OnUnloaded() override;
    virtual void Update() override;

    void LoadResources();

    static void Count();

    void CreateChampPanel(int borderW, int borderH, int padding);

    LoadingChampScreen* screens[10] = {};
};

