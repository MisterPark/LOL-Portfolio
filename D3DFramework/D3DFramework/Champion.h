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

    virtual void Die();
    virtual void OnHit(Unit* target, Skill* mySkill) override;
    virtual void OnDamaged(Unit* target, Skill* targetSkill, float* damage) override;
    virtual void OnKilled(Unit* target) override;
    //챔피언이 스킬을 사용할떄마다, [장비아이템 스킬]에서 호출 // Ex)광휘의검
    virtual void OnOtherSkillStart(Skill* otherSkill);
    //스킬로 공격중일때, 대상들을 처음 떄릴마다 [장비아이템 스킬]에서 호출 // Ex) 굶주린 히드라
    virtual void OnTargetFirstHit(Unit* target, Skill* mySkill);

    void RealTimeGoldIncrease();
public:
    
	FloatingHPBar* hpBar = nullptr;
    wstring faceCircleTexkey;
    wstring faceSquareTexkey;

    wstring qTexKey;
    wstring wTexKey;
    wstring eTexKey;
    wstring rTexKey;
    wstring passiveTexKey;

    wstring nickname;

    float realTimeGoldTick = 0.f;
};

