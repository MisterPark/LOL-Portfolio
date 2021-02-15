#pragma once
#include "GameObject.h"
#include "Unit.h"
using namespace PKH;

class Label;

class FloatingBar : public GameObject
{
public:
    FloatingBar();
    virtual ~FloatingBar();

    virtual void Initialize() override;
    virtual void Release() override;
    virtual void Update() override;


    void SetTarget(Unit* target);
    void SetTexture(const wstring& _textureKey);
    void SetTextureHP(const wstring& _textureKey);
    void SetTextureMP(const wstring& _textureKey);
    void SetNickname(const wstring& _nick);

protected:
    Unit* target = nullptr;

    Vector3 offset;
    wstring textureKey;
    //HP
    wstring textureKeyHP;
    Vector3 offset2;
    Vector3 scaleHP;
    //MP
    wstring textureKeyMP;
    Vector3 offsetMP;
    Vector3 scaleMP;

    Label* nicknameLabel = nullptr;
    //PKH::Rectangle* mesh = nullptr;

    //bool isHover = false;
};
