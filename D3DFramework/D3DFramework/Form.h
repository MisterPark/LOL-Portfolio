#pragma once
#include "UI.h"


class Form :
    public Engine::UI
{
    enum class pos { lt, t, rt, l, c, r, lb, b, rb, end };

public:
    Form(const Vector2& size, const Vector2& pos);
    virtual ~Form();

    virtual void Initialize() override;
    virtual void Release() override;
    virtual void Update() override;

    virtual Vector2 GetSize();
    void SetSize(const Vector2& _size);

private:
    UI* ui[(UINT)pos::end];
    Vector2 size;
};

