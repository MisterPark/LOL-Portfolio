﻿#pragma once
#include "Panel.h"

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

    void ShowVictory();
    void ShowDefeat();

private:
    UI* victoryBack = nullptr;
    UI* victoryFont = nullptr;
    UI* defeatBack = nullptr;
    UI* defeatFont = nullptr;
    Button* btnContinue = nullptr;
};

