#pragma once

class Unit;

class Skill abstract
{
public:
	Skill();
	virtual ~Skill();

	virtual void Start() = 0;
	virtual void Passive() = 0;
	virtual void Active() = 0;
	virtual void End() = 0;
	void SetActive(bool _active) { active = _active; }
	bool IsActive() { return active; }
	bool IsAvailable();

protected:
	Unit* hostUnit = nullptr;
	float coolTime_Init = 0.f;
	float coolTime = 0.f;
	float duration = 0.f;
	int level = 0;
	bool active = false;
	
};

