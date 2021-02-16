#pragma once
#include "HUD.h"
class MinimapPanel :
    public HUD
{
private:
    MinimapPanel();
    virtual ~MinimapPanel();
public:
    static MinimapPanel* GetInstance();
    static void Destroy();

    static void TestFunc();
};

