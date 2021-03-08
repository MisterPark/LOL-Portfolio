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
    void Minimap_MouseClick(GameObject* sender, MouseEventArg* arg);
    static void Static_Minimap_MouseClick(GameObject* sender, MouseEventArg* arg);
};

