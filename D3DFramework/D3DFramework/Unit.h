#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Stat.h"
#include "Stat.h"
#include "DamageCalc.h"
#include "Skill.h"

class Indicator;

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

enum class SkillIndex
{
	Passive,
	Q,
	W,
	E,
	R,
	D,
	F,
	END
};

class Unit : public GameObject
{
public:
    Unit();
    virtual ~Unit();

    virtual void Initialize() override;
    virtual void Release() override;
    virtual void Update() override;

	void UpdateLastAttacker();

	void LookRotation(Vector3 _direction);
	void SetDestination(Vector3 _target);
	void Move(Vector3 _target);
	virtual void Chase(Vector3 _target);

	virtual void Attack(Unit* _target);
	virtual void Attacked();
	void Spell1();
	void Spell2();
	void Spell3();
	void Spell4();

	virtual void Die();
	// 행동
	void DeadAction();
	void AttackAction();
	void CounterAttack();
	void IdleAction();
	void MoveAction();
	virtual void SkillQAction();
	virtual void SkillWAction();
	virtual void SkillEAction();
	virtual void SkillRAction();

	void PushedOut(Unit* other);

	void SetState(State _state);
	State GetState();

	virtual void SetTeam(Team _team);
	Team GetTeam();
	void SetAttackTarget(Unit* _target);
	Unit* GetAttackTarget();

	void SetAttackPerSec(float _attackPerSec);

	void SetLastAttacker(Unit* _attacker);

	void TakeDamage(float _damage);
	void SetID(INT _id);

	bool IsDead();
	bool HasAttackTarget();
	bool HasLastAttacker();

	void Calc_FinalDamage(float* _damage, Stat* _myStat, Stat* _targetStat);

	INT GetID();

	Unit* GetLastAttacker();
	Unit* GetNearestEnemy(Vector3 point, float radius = INFINITY);
	void SetAttackState(State _attackState) { attackState = _attackState; }
	// 멀티
	void ReqMove(Vector3 _dest, bool _noSearch = false);
	void ReqAttack(Unit* _target);
	void ReqDamage(INT _attackerID, INT _targetID, float _damage);
	
	
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

public:
	// 이동모션 관련
	State moveState = State::RUN;
	State attackState = State::ATTACK1;
	State state = State::IDLE1;
	
	// 기본공격 관련
	bool attackFlag = false;
	Unit* attackTarget = nullptr;
	float attackTick = 0.f;
protected:
	

	// 스킬 관련
	Skill* skillList[MaxOfEnum<SkillIndex>()];
	
	// 데미지계산관련
	list<DamageCalc*> damageCalcList;

	// 마지막으로 나를 공격한 유닛
	Unit* lastAttacker = nullptr;
	float lastAttackTick = 0.f;
	float lastAttackDuration = 5.f;

	bool isDamaged = false;

	// 추격 관련
	float chaseTick = 0.f;
	float chaseDelay = 0.3f;

	// 사망 관련
	bool isDead = false;
	
	// 네트워크 관련
	INT unitID = -1;
public:
};

