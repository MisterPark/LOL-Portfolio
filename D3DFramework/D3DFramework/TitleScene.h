#pragma once
#include "Scene.h"
#include "LobbyWindow.h"

class TitleScene :
    public Scene
{
public:
    // Scene을(를) 통해 상속됨
    virtual void OnLoaded() override;
    virtual void OnUnloaded() override;
    virtual void Update() override;

    LobbyWindow* lobby = nullptr;
};

