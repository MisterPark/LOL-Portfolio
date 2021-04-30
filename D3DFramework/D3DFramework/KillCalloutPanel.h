#pragma once
#include "Panel.h"

class Button;
class KillCalloutUI;

class KillCalloutPanel :
    public Panel
{
public:
    KillCalloutPanel();
    virtual ~KillCalloutPanel();
public:
    static KillCalloutPanel* GetInstance();
    static void DestroyInstance();

    virtual void Update() override;

    void AddKillCallout(const std::wstring _faceL, const std::wstring _faceR, Team _team);
    
private:
    list<KillCalloutUI*> killList;
};

