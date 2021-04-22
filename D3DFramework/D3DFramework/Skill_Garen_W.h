#pragma once
#include "Skill.h"
#include "Unit.h"

class Buff_GarenWPassive;
class Skill_Garen_W :
    public Skill
{
public:
    Skill_Garen_W(Unit* _hostUnit);
    virtual ~Skill_Garen_W();

    virtual void Start();
    virtual void Passive();
    virtual void Active();
    virtual void End();
    virtual void OnKilled(Unit* target) override;
    void AddPassiveStack() { if(passiveStack < 30)passiveStack++; }
    int GetPassiveStack() { return passiveStack; }
    
private:
    float reductionTime = 0.35f;
    int passiveStack = 0;
    Buff_GarenWPassive* passiveBuff = nullptr;
    //float reductionValue = 0.65f;

    //float baseShield = 45.f;
    //float growthShield = 25.f;
};


