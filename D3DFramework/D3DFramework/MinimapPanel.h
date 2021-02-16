#pragma once
#include "Panel.h"
class MinimapPanel :
    public Panel
{
private:
    MinimapPanel();
    virtual ~MinimapPanel();
public:
    static MinimapPanel* GetInstance();
    static void Destroy();

    static void TestFunc();
};

