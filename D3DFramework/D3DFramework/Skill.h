#pragma once

class Unit;

class Skill abstract
{
public:
	Skill();
	virtual ~Skill();

	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void End() = 0;
	
protected:
	Unit* hostUnit = nullptr;
	float coolTime_Init = 0.f;
	float coolTime = 0.f;
	float duration = 0.f;
	int level = 0;
	
};

