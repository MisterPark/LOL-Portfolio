#pragma once
#include "Panel.h"
class MinimapPanel :
    public Panel
{
public:
    MinimapPanel();
    virtual ~MinimapPanel();
public:
    static MinimapPanel* GetInstance();
    static void DestroyInstance();

    static void TestFunc();
};

