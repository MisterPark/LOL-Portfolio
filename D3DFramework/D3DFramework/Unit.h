#pragma once
#include "GameObject.h"
#include "Animation.h"

enum class Team
{
	NEUTRAL, BLUE, RED, END
};

enum class UnitState
{
	IDLE1,
	IDLE2,
	IDLE3,
	DEATH,
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


	void UpdateState();

	void LookRotation(Vector3 _direction);
	void SetDestination(Vector3 _target);
	void Move(Vector3 _target);
	virtual void Attack(Unit* _target);
	virtual void Spell1();
	virtual void Spell2();
	virtual void Spell3();
	virtual void Spell4();

	virtual void Die();

	void PushedOut(Unit* other);

	virtual void SetTeam(Team _team);
	void SetAttackTarget(Unit* _target);
	void SetAttackSpeed(float _attackPerSec);
	void SetMovementSpeed(float _speed);
	void TakeDamage(float _damage);
	void SetID(INT _id);

	bool IsDead();
	INT GetID();

public:
	UnitState state = UnitState::IDLE1;
	Team team = Team::NEUTRAL;
	Animation* anim = nullptr;
	NavMeshAgent* agent = nullptr;
	SphereCollider* collider = nullptr;

protected:
	// 기본공격 관련
	bool attackFlag = false;
	Unit* attackTarget = nullptr;
	float attackRange = 1.25f;
	float attackTick = 0.f;
	float attackPerSec = 0.625f;
	UnitState attackState = UnitState::ATTACK1;
	bool canAttack = false;

	bool isDamaged = false;
	// 추격 관련
	float chaseTick = 0.f;
	float chaseDelay = 0.1f;

	// 사망 관련
	bool isDead = false;
	
	// 네트워크 관련
	INT unitID = -1;
public:
	float attackDamage = 15;
	float armor = 1;
	float magicResistance = 1;
	float movementSpeed = 5.f;

	float hp = 100;
	float maxHp = 100;
	float mp = 100;
	float maxMp = 100;
	float exp = 100;
	float maxExp = 100;
};

