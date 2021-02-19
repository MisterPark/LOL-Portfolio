#pragma once
#include "UI.h"


class OutlinedSlot :
    public PKH::UI
{
    enum class type { outline, icon, end };

public:
    OutlinedSlot(const std::wstring& _tagOutline, const Vector2& pos, bool backicon = true);
    virtual ~OutlinedSlot();

    virtual void Initialize() override;
    virtual void Release() override;
    virtual void Update() override;

    void SetIcon(const std::wstring& _tag);

    UI* outline = nullptr;
    UI* icon = nullptr;
};

