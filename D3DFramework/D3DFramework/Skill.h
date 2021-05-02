#pragma once
#include "DamageCalc.h"
#define NON_COMBAT_TIME 5.f
class Unit;
class Skill abstract
{
public:
	enum class ItemSkillName {
		None, HealthPotion,
		ManaCharge, 
		Cleave, Crescent, Immolate, Nimble, Precision, SpellBlade, SteelTipped, Thorns, WitchFocus,
		WraithStep, Dreadnought,
		END
	};
public:
	Skill();
	virtual ~Skill();

	virtual void Use();
	virtual void Start() = 0;
	virtual void Passive() = 0;
	virtual void Active() = 0;
	virtual void End() = 0;
	virtual void Cancel() {};
	virtual bool InRange();

	virtual Skill* Clone();

	//플레이어가 피해를 주었을때 호출
	virtual void OnHit(Unit* target, Skill* mySkill);
	//플레이어가 피해를 입었을때 호출
	virtual void OnDamaged(Unit* target, Skill* targetSkill, float* damage);
	//플레이어가 적을 죽였을때 호출
	virtual void OnKilled(Unit* target);
	//이 스킬로 피해를 줬을때만 호출
	virtual void OnThisSkillHit(Unit* target);
	//챔피언이 스킬을 사용할떄마다, [장비아이템 스킬]에서 호출 // Ex)광휘의검
	virtual void OnOtherSkillStart(Skill* otherSkill);
	//스킬로 공격중일때, 대상들을 처음 떄릴마다 [장비아이템 스킬]에서 호출 // Ex) 굶주린 히드라
	virtual void OnTargetFirstHit(Unit* target, Skill* mySkill);

	static bool PlayerToDistanceCompare(Vector3 _pos, float _distance = 10.f);

	void SetActive(bool _active) { active = _active; }
	bool IsActive();
	bool IsAvailable();

	void Add_DamageCalc(DamageCalc* _damageCalc);
	void Calc_FinalDamage(float* _damage, Stat* _myStat, Stat* _targetStat);
	void Calc_TakeDamege(float _baseDamage);
	float GetCooltime();
	float GetCooltime_Init();
	int GetLevel() { return level; }
	int GetMaxLevel() { return maxLevel; }
	Unit* GetHost() { return host; }
	void AddLevel() { level++; }
	float GetRange() { return range; }
	list<Unit*>* GetHitList() { return &hitList; }
	ItemSkillName GetSkillName() { return skillName; }
	
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
	//OnThisSkillHit 에서 쓸용도 (스킬 한번당 한번의 공격 체크용) Ex)여눈, 감전등
	bool firstHit = false;
	// 데미지계산관련
	list<DamageCalc*> damageCalcList;
	// 공격한리스트
	list<Unit*> hitList;
	ItemSkillName skillName = ItemSkillName::None;

public:
	int overlapCount = 1;
};

