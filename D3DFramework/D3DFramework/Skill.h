#pragma once
#include "DamageCalc.h"

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

	void Add_DamageCalc(DamageCalc* _damageCalc);
	void Calc_FinalDamage(float* _damage, Stat* _myStat, Stat* _targetStat);

	float GetCooltime();
	float GetCooltime_Init();

protected:
	Unit* hostUnit = nullptr;
	float coolTime_Init = 0.f;
	float coolTime = 0.f;
	float duration = 0.f;
	int level = 0;
	bool active = false;
	
	// 데미지계산관련
	list<DamageCalc*> damageCalcList;
};

