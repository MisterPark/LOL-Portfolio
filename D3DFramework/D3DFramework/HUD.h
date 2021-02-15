#pragma once
#include "UI.h"

class HUD :
    public UI
{
public:
    HUD();
    HUD(const std::wstring& _key, Vector2 _pos);
    HUD(const std::wstring& _key);
    virtual ~HUD();

    // UI을(를) 통해 상속됨
    virtual void Initialize() override;
    virtual void Release() override;
};

