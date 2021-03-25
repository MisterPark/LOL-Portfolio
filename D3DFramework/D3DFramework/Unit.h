#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Stat.h"
#include "Stat.h"
#include "DamageCalc.h"
#include "Skill.h"
#include "Inventory.h"

class Indicator;
class TargetingSkill;

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

	void TakeDamage(float _damage);
	float DecreaseShieldBuff(float _damage);
	void SetID(INT _id);

	Vector3 GetSpawnPosition();
	void SetSpawnPosition(Vector3 _spawnPos);
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
	void SetAttackState(State _attackState) { attackState = _attackState; }
	void SkillLevelUp(SkillIndex skillIndex);
	// 멀티
	void ReqMove(Vector3 _dest, bool _noSearch = false);
	void ReqAttack(Unit* _target);
	void ReqDamage(INT _attackerID, INT _targetID, float _damage);
	
	// 인벤토리
	bool AddItem(Item* _item);
	
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

