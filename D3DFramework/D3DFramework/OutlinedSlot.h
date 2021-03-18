#pragma once
#include "UI.h"


class OutlinedSlot :
    public Engine::UI
{
    enum class type { outline, icon, end };

public:
    OutlinedSlot(const std::wstring& _tagOutline, const Vector2& pos, bool backicon = true);
    virtual ~OutlinedSlot();

    virtual void Initialize() override;
    virtual void Release() override;
    virtual void Update() override;

    void SetIcon(const std::wstring& _tag);
    void SetCooltime(float _cooltime, float _cooltimeMax);

    UI* outline = nullptr;
	UI* icon = nullptr;
private:
    UIRenderer* renderer;
    float cooltime = 0.f;
    float cooltimeMax = 0.f;
};

