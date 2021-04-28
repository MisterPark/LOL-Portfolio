#pragma once
#include "Panel.h"

class Champion;
class MinimapPanel :
    public Panel
{
public:
    MinimapPanel();
    virtual ~MinimapPanel();
public:
    static MinimapPanel* GetInstance();
    static void DestroyInstance();

    virtual void Update() override;

    static void TestFunc();
    void Minimap_MouseClick(GameObject* sender, MouseEventArg* arg);
    static void Static_Minimap_MouseClick(GameObject* sender, MouseEventArg* arg);

    void AddChampion(Champion* _champ);

private:
    vector<Champion*> champ[2];
    vector<UI*> champFace[2];
};

