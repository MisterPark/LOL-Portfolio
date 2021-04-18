#pragma once
#include "Skill.h"
#include "Buff_Item_SteelTipped.h"
class Skill_Item_SteelTipped : // 곡궁
    public Skill
{
public:
	Skill_Item_SteelTipped(Unit* _hostUnit);
	virtual ~Skill_Item_SteelTipped();

	virtual void Start() override;
	virtual void Passive() override;
	virtual void Active() override;
	virtual void End() override;
	virtual Skill* Clone() override;

private:
	Buff_Item_SteelTipped* buffSkill = nullptr;
};

