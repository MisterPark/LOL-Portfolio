#pragma once
#include "TargetingSkill.h"
class Skill_RangeAttack :
    public TargetingSkill
{
public:
    Skill_RangeAttack(Unit* _hostUnit);
    virtual ~Skill_RangeAttack();
    virtual void Start() override;
    virtual void Passive() override;
    virtual void Active() override;
    virtual void End() override;

    void AttackCancleToAttack();
    void SetTexture(const wstring& _key);

private:
    wstring textureKey = L"missfortune_base_e_musketball";
    bool beginAttackFlag = false;
};

