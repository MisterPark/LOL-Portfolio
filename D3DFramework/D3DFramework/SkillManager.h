#pragma once
#include "Skill.h"

class SkillManager
{
private:
	SkillManager();
	~SkillManager();

public:
	static SkillManager* GetInstance();
	static void Destroy();

public:
	void Update();
	void PostUpdate();

public:
	void AddSkillToList(Skill* skill);
	void DeleteSkillFromList(Skill* skill);
	bool IsSkillInList(Skill* skill);

public:
	static Skill* GetSkill(SkillName skillName);

private:
	static SkillManager* instance;
	list<Skill*> skillList;
};

