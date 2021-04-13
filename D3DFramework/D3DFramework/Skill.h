#pragma once
#include "DamageCalc.h"

class Unit;
class Skill abstract
{
public:
	Skill();
	virtual ~Skill();

	virtual void Use();
	virtual void Start() = 0;
	virtual void Passive() = 0;
	virtual void Active() = 0;
	virtual void End() = 0;
	virtual bool InRange();
	virtual void OnHit(Unit* target);
	virtual void OnDamaged(float damage);

	void SetActive(bool _active) { active = _active; }
	bool IsActive();
	bool IsAvailable();

	void Add_DamageCalc(DamageCalc* _damageCalc);
	void Calc_FinalDamage(float* _damage, Stat* _myStat, Stat* _targetStat);

	float GetCooltime();
	float GetCooltime_Init();
	int GetLevel() { return level; }
	int GetMaxLevel() { return maxLevel; }
	void AddLevel() { level++; }
	float GetRange() { return range; }
	
	virtual bool TargetingSuccess(Unit* target);

	void SetTarget(Unit* _target);

protected:
	Unit* host = nullptr;
	float coolTime = 0.f;
	float coolTimeTick = 0.f;
	float tick = 0.f;
	float duration = 0.f;
	int level = 0;
	int maxLevel = 1;
	bool active = false;
	float range = 0.f;

	
	// 데미지계산관련
	list<DamageCalc*> damageCalcList;
};

