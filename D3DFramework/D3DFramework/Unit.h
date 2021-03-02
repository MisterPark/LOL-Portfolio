#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Stat.h"
#include "UnitStat.h"

class Indicator;

enum class UnitState
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
	virtual void Spell1();
	virtual void Spell2();
	virtual void Spell3();
	virtual void Spell4();

	virtual void Die();
	// 행동
	void DeadAction();
	void AttackAction();
	void CounterAttack();
	void IdleAction();

	void PushedOut(Unit* other);

	void SetState(UnitState _state);
	UnitState GetState();

	virtual void SetTeam(Team _team);
	void SetAttackTarget(Unit* _target);
	Unit* GetAttackTarget();

	void SetHP(float _max);
	void SetMP(float _max);
	void SetHPRegen(float _per5Sec);
	void SetMPRegen(float _per5Sec);
	void SetAttackDamage(float _damage);
	void SetAttackPerSec(float _attackPerSec);
	void SetAttackRange(float _range);
	void SetAbilityPower(float _ap);
	void SetMovementSpeed(float _speed);
	void SetArmor(float _armor);
	void SetMagicResistance(float _magicResist);
	void SetCriticalPer(float _percent);
	void SetCooldownReduction(float _cdr);

	void SetLastAttacker(Unit* _attacker);

	void TakeDamage(float _damage);
	void SetID(INT _id);

	bool IsDead();
	bool HasAttackTarget();
	bool HasLastAttacker();

	INT GetID();
	float GetHP();
	float GetMP();
	float GetMaxHP();
	float GetMaxMP();
	float GetAttackDamage();
	float GetAttackPerSec();
	float GetAttackRange();
	float GetAbilityPower();
	float GetMovementSpeed();
	float GetArmor();
	float GetMagicResistance();
	float GetCriticalPer();
	float GetCooldownReduction();

	Unit* GetLastAttacker();
	Unit* GetNearestEnemy(Vector3 point, float radius = INFINITY);

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
	UnitStat* stat = nullptr;
	BehaviorTree* bt = nullptr;

protected:
	UnitState state = UnitState::IDLE1;
	
	// 기본공격 관련
	bool attackFlag = false;
	Unit* attackTarget = nullptr;
	float attackRange = 1.25f;
	float attackTick = 0.f;
	float attackPerSec = 0.625f;
	UnitState attackState = UnitState::ATTACK1;

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

