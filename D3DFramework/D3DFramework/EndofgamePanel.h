#pragma once
#include "Panel.h"
#include "EventSystem.h"

class Button;
class EndofgamePanel :
    public Panel
{
public:
    EndofgamePanel();
    virtual ~EndofgamePanel();
public:
    static EndofgamePanel* GetInstance();
    static void DestroyInstance();

    virtual void Update() override;

    void ShowVictory();
    void ShowDefeat();

    void Shutdown(GameObject* sender, MouseEventArg* arg);

private:
    UI* victoryBack = nullptr;
    UI* victoryFont = nullptr;
    UI* defeatBack = nullptr;
    UI* defeatFont = nullptr;
    Button* btnContinue = nullptr;

    vector<UI*> backeffect;
    int effectidx = 0;
    bool isVictory = true;
};

