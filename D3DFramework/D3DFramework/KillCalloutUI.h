#pragma once
#include "Panel.h"

// UI 1개
// KillCalloutPanel에서 생성하고 관리
class Button;
class KillCalloutUI :
    public Panel
{
public:
    KillCalloutUI(const std::wstring& _faceL, const std::wstring& _faceR, const Team _team);
    virtual ~KillCalloutUI();
public:
    virtual void Update() override;

    virtual Vector2 GetSize() override;
    void SetAlpha(float _alpha);
    bool IsEnd();

private:
    Team team;
    UI* background = nullptr;
    UI* icon = nullptr;
    UI* faceL = nullptr;
    UI* faceR = nullptr;

    float tick = 0.f;
    float duration = 5.f;
    float alpha = 0.f;

};

