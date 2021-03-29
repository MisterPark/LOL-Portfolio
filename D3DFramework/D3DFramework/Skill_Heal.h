#pragma once
#include "Skill.h"
class Skill_Heal :
    public Skill
{
public:
    Skill_Heal(Unit* _hostUnit);
    virtual ~Skill_Heal();

    virtual void Start();
    virtual void Passive();
    virtual void Active();
    virtual void End();

private:
    void Heal();
    Unit* GetLostHpTeam(Vector3 point, float radius);
};

