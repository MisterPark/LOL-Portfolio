﻿#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Stat.h"
#include "Stat.h"
#include "DamageCalc.h"
#include "Skill.h"
#include "Inventory.h"
#include "Aura.h"

class Indicator;
class TargetingSkill;
class Skill_Attack;

enum class UnitID
{
	Champ0, Champ1, Champ2, Champ3, Champ4, Champ5, Champ6, Champ7, Champ8, Champ9,
	TurretBlueBot1,
	TurretBlueBot2,
	TurretBlueBot3,
	TurretBlueMid1,
	TurretBlueMid2,
	TurretBlueMid3,
	TurretBlueTop1,
	TurretBlueTop2,
	TurretBlueTop3,
	TurretBlueTwin1,
	TurretBlueTwin2,
	InhibitorBlueBot,
	InhibitorBlueMid,
	InhibitorBlueTop,
	NexusBlue,

	TurretRedBot1,
	TurretRedBot2,
	TurretRedBot3,
	TurretRedMid1,
	TurretRedMid2,
	TurretRedMid3,
	TurretRedTop1,
	TurretRedTop2,
	TurretRedTop3,
	TurretRedTwin1,
	TurretRedTwin2,

	Red1,
	Red2,
	Blue1,
	Blue2,
	Murkwolf1,
	Murkwolf_Mini1,
	Murkwolf_Mini2,
	Murkwolf2,
	Murkwolf_Mini3,
	Murkwolf_Mini4,
	Gromp1,
	Gromp2,
	Razorbeak1,
	Razorbeak_Mini1,
	Razorbeak_Mini2,
	Razorbeak_Mini3,
	Razorbeak_Mini4,
	Razorbeak_Mini5,
	Razorbeak2,
	Razorbeak_Mini6,
	Razorbeak_Mini7,
	Razorbeak_Mini8,
	Razorbeak_Mini9,
	Razorbeak_Mini10,
	Krug1,
	Krug2,
	Scuttleracer1,
	Scuttleracer2,
	END
};

enum class State
{
	IDLE1,
	IDLE2,
	IDLE3,
	DEATH,
	DEATH2,
	RECALL,
	RECALL2,
	RECALL3,
	RUN,
	RUN2,
	RUN_HASTE,
	ATTACK1,
	ATTACK2,
	ATTACK3,
	ATTACK4,
	CRITICAL,
	Q,
	W,
	E,
	R,
	Q2,
	W2,
	E2,
	R2,
	SPAWN,
	END
};

enum class SkillIndex { Attack, Passive, Q, W, E, R, D, F, END };

class Unit : public GameObject
{
public:
	struct HitInfo
	{
		float tick = 0.f;
		float duration = 10.f;
		float damageSum = 0.f;
		Unit* unit = nullptr;
	};
public:
    Unit();
    virtual ~Unit();

    virtual void Initialize() override;
    virtual void Release() override;
    virtual void Update() override;

	void UpdateHit(); // 피격 업데이트
	void UpdateSpawn(); // 스폰 업데이트

	void LookRotation(Vector3 _direction);
	void SetDestination(Vector3 _target);
	void Move(Vector3 _target);
	virtual void Chase(Vector3 _target);
	void ChaseTarget();
	virtual void OnAttackBegin();
	virtual void OnAttackEnd();
	void Attack();
	void Spell1();
	void Spell2();
	void Spell3();
	void Spell4();
	void Spell5();
	void Spell6();

	virtual void Die();
	virtual void OnKilled(Unit* target);
	virtual void OnHit(Unit* target, Skill* mySkill);
	virtual void OnDamaged(Unit* target, Skill* targetSkill, float damage);
	//챔피언이 스킬을 사용할떄마다, [장비아이템 스킬]에서 호출 // Ex)광휘의검
	virtual void OnOtherSkillStart(Skill* otherSkill);
	//스킬로 공격중일때, 대상들을 처음 떄릴마다 [장비아이템 스킬]에서 호출 // Ex) 굶주린 히드라
	virtual void OnTargetFirstHit(Unit* target, Skill* mySkill);

	// 행동
	virtual void DeadAction();
	virtual void AttackAction();
	virtual void CounterAttack();
	virtual void IdleAction();
	virtual void MoveAction();
	virtual void SkillQAction();
	virtual void SkillWAction();
	virtual void SkillEAction();
	virtual void SkillRAction();

	void PushedOut(Unit* other);
	void Respawn();

	// getter, setter
	void SetState(State _state);
	State GetState();

	virtual void SetTeam(Team _team);
	Team GetTeam();
	void SetAttackTarget(Unit* _target);
	Unit* GetAttackTarget();

	void SetAttackPerSec(float _attackPerSec);

	void SetLastAttacker(Unit* _attacker);
	void SetAttackPoint(Vector3 _pos);
	void SetNextSkill(Skill* _skill);
	void SetNextSkillReady(Skill* _skill);
	void TakeNextSkill();

	void TakeDamage(float _damage);
	float DecreaseShieldBuff(float _damage);
	void SetID(INT _id);

	Vector3 GetSpawnPosition();
	void SetSpawnPosition(Vector3 _spawnPos);
	void SetSpawnTime(float _delay);
	float GetRemainingRespawnTime();


	bool IsDead();
	bool HasAttackTarget();
	bool HasLastAttacker();
	bool HasNextSkill();

	void StartNextSkill();

	void Calc_FinalDamage(float* _damage, Stat* _myStat, Stat* _targetStat);

	INT GetID();

	Unit* GetLastAttacker();
	Unit* GetNearestEnemy(Vector3 point, float radius = INFINITY);
	bool IsEnemyInAttackRange();
	bool IsTargetInAttackRange();
	void SetAttackState(State _attackState) { attackState = _attackState; }
	void SkillLevelUp(SkillIndex skillIndex);
	Skill_Attack* GetSkillAttack();
	template<class T>
	Unit::HitInfo GetLastHitInfo();
	// 멀티
	void ReqMove(Vector3 _dest, bool _noSearch = false);
	void ReqAttack(Unit* _target);
	void ReqDamage(INT _attackerID, INT _targetID, float _damage);
	
	// 인벤토리
	bool AddItem(UINT _id); // 인벤토리에 그냥 아이템을 집어넣음
	bool BuyItem(UINT _id); // 골드를 깎으면서 아이템을 집어넣음
	void SellItem(int _idx);
	
public:
	static list<Unit*> unitList;
public:
	Team team = Team::NEUTRAL;
	Animation* anim = nullptr;
	NavMeshAgent* agent = nullptr;
	SphereCollider* collider = nullptr;
	Indicator* attackIndicator = nullptr;
	Stat* stat = nullptr;
	BehaviorTree* bt = nullptr;
	Aura* aura = nullptr;

public:
	// 이동모션 관련
	State moveState = State::RUN;
	State attackState = State::ATTACK1;
	State state = State::IDLE1;
	
	// 기본공격 관련
	Unit* attackTarget = nullptr;
	Vector3 attackPoint;
	float attackTick = 0.f;
	bool attackFlag = false; // 공격(데미지 입히기) 가능 여부
	bool hitFlag = false; // 피격당할때(트리거)

private:
	bool oldHitFlag = false;
public:
	list<HitInfo> hitList;
	// 스킬 관련
	Skill* skillList[MaxOfEnum<SkillIndex>()];
	Skill* nextSkill = nullptr;
	Skill* nextSkillReady = nullptr;
private:
	// 스폰
	Vector3 spawnPosition;
	float spawnTick = 0.f;
	float spawnDelay = 10.f;
	bool spawnFlag = false;

public:
	// 인벤토리
	Inventory inventory;

protected:
	// 데미지계산관련
	list<DamageCalc*> damageCalcList;

	// 마지막으로 나를 공격한 유닛
	Unit* lastAttacker = nullptr;
	float lastAttackTick = 0.f;
	float lastAttackDuration = 5.f;


	// 추격 관련
	float chaseTick = 0.f;
	float chaseDelay = 0.3f;

	// 사망 관련
	bool isDead = false;
	
	// 네트워크 관련
	INT unitID = -1;
private:
	State oldAttackState = State::IDLE1;
	bool beginAttackFlag = false;

};

