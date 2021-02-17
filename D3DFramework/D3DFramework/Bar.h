#pragma once
#include "UI.h"


class Bar :
    public UI
{
public:
    Bar();
    Bar(const std::wstring& _tag, const Vector2& pos);
    virtual ~Bar();

    float GetRatio();
    void SetRatio(float _ratio);

protected:
    float ratio = 1.f;
};

