#pragma once
#include "Skill.h"
class Skill_Ghost :
    public Skill
{
public:
    Skill_Ghost(Unit* _hostUnit);
    virtual ~Skill_Ghost();

    virtual void Start();
    virtual void Passive();
    virtual void Active();
    virtual void End();
};

