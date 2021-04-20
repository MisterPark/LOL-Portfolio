#pragma once
#include "GameObject.h"
#include "Unit.h"
using namespace Engine;

class Bar;
class Label;

class FloatingBar : public UI
{
public:
    FloatingBar();
    virtual ~FloatingBar();

    virtual void Update() override;
    virtual void PostUpdate() override;

    void SetTarget(Unit* target);
    void SetTextureHP(const wstring& _key);
    void SetTextureMP(const wstring& _key);
    void SetNickname(const wstring& _nick);
    void SetOffset(Vector3 _offset);

protected:
    Unit* target = nullptr;

    Vector3 offset;
    wstring textureKey;

    Bar* hpBar = nullptr;
    Bar* mpBar = nullptr;
    Bar* shieldBar = nullptr;
    Bar* overShieldBar = nullptr;
    Label* nickLabel = nullptr;
};
