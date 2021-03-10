#pragma once
#include "Unit.h"

class FloatingBar;
class FloatingHPBar;

class Champion :
    public Unit
{
public:

    Champion();
    virtual ~Champion();

    virtual void Initialize() override;
    virtual void Release() override;
    virtual void Update() override;

    virtual void OnCollisionEnter(Collider* target);

    virtual void SetTeam(Team _team);
    void SetNickname(const std::wstring& _nickname);

public:
    FloatingBar* bar = nullptr;
	FloatingHPBar* hpBar = nullptr;
    wstring faceCircleTexkey;
    wstring faceSquareTexkey;

    wstring qTexKey;
    wstring wTexKey;
    wstring eTexKey;
    wstring rTexKey;
    wstring passiveTexKey;

    wstring nickname;
};

