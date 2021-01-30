#include "stdafx.h"
#include "Unit.h"
#include "SphereCollider.h"
#include "NavMeshAgent.h"
#include "Animation.h"
#include "Indicator.h"

Unit::Unit()
{
	anim = (Animation*)AddComponent<Animation>(L"Animation");
	collider = (SphereCollider*)AddComponent<SphereCollider>(L"SphereCollider");
	collider->SetRadius(0.5f);
	collider->center = { 0.f,1.f,0.f };

	agent = (NavMeshAgent*)AddComponent< NavMeshAgent>(L"NavMeshAgent");

	attackIndicator = (Indicator*)ObjectManager::GetInstance()->CreateObject<Indicator>(Layer::Indicator);
	attackIndicator->SetTarget(this);

	SetAttackPerSec(0.625f);
}

Unit::~Unit()
{
	anim = nullptr;
	agent = nullptr;
	attackIndicator = nullptr;
}

void Unit::Initialize()
{
}

void Unit::Release()
{
}

void Unit::Update()
{
	state = UnitState::IDLE1;

	UpdateState();

	GameObject::Update();

}


void Unit::UpdateState()
{
	float dt = TimeManager::DeltaTime();
	
	if (isDead)
	{
		state = UnitState::DEATH;
		attackTarget = nullptr;
		UINT curAnim = anim->GetCurrentAnimation();
		UINT deathAnim = anim->GetIndexByState(UnitState::DEATH);
		if (curAnim == deathAnim && anim->IsFrameEnd())
		{
			anim->Stop();
		}
		return;
	}

	if (anim->IsFrameEnd())
	{
		int rand = Random::Range(0, 9);
		if (rand < 5)
		{
			attackState = UnitState::ATTACK1;
		}
		else
		{
			attackState = UnitState::ATTACK2;
		}
	}

	if (attackTarget != nullptr)
	{
		if (attackTarget->IsDead())
		{
			attackTarget = nullptr;
			return;
		}
		Vector3 direction = attackTarget->transform->position - transform->position;
		float dist = direction.Length();
		if (dist <= attackRange) // 공격 거리 이내
		{
			LookRotation(direction.Normalized());
			state = attackState;

			attackTick += dt;
			float attackDelay = 1.f / attackPerSec;
			if (attackTick > attackDelay)
			{
				attackTick = 0.f;
				canAttack = true;
			}
			float damageDelay = attackDelay * 0.1f;
			if (attackTick > damageDelay)
			{
				if (isDamaged == false)
				{
					isDamaged = true;
					attackTarget->TakeDamage(attackDamage);
				}
			}
			

			if (canAttack == false) return;


			canAttack = false;
			isDamaged = false;
		}
		else
		{
			chaseTick += dt;
			if (chaseTick > chaseDelay)
			{
				chaseTick = 0.f;
				agent->SetStoppingDistance(attackRange);
				SetDestination(attackTarget->transform->position);
			}
			
		}
	}
	else
	{
		isDamaged = false;
	}
	
}

void Unit::LookRotation(Vector3 _direction)
{
	float angle = Vector3::AngleY(Vector3(0, 0, 1), _direction);
	transform->eulerAngles.y = angle;
}

void Unit::SetDestination(Vector3 _target)
{
	
	Vector3 direction = _target - transform->position;
	Vector3::Normalize(&direction);

	// 이동
	Ray ray2;
	RaycastHit hit2;
	ray2.origin = transform->position;
	ray2.origin.y += 0.1f;
	ray2.direction = direction;
	float dist = Vector3(_target - ray2.origin).Length();
	int mask2 = LayerMask::GetMask(Layer::Wall);
	if (Physics::Raycast(ray2, &hit2, dist, mask2))
	{
		// 직선상에 벽이 있을 경우
		Debug::Print("직선상에 벽이있음\n");
		agent->SetDestination(_target);
	}
	else
	{
		// 직선상에 벽이 없을 경우
		agent->SetDestination(_target, true);
	}
}

void Unit::Move(Vector3 _target)
{
	SetAttackTarget(nullptr);
	agent->SetStoppingDistance(0.03f);
	SetDestination(_target);
}

void Unit::Attack(Unit* target)
{
	if (target == nullptr) return;

	attackTarget = target;
	
	//agent->SetStoppingDistance(attackRange);
	//SetDestination(attackTarget->transform->position);
}

void Unit::Spell1()
{
}

void Unit::Spell2()
{
}

void Unit::Spell3()
{
}

void Unit::Spell4()
{
}

void Unit::Die()
{
	isDead = true;
	collider->enable = false;
}

void Unit::PushedOut(Unit* other)
{
	Vector3 direction = collider->GetWorldPosition() - other->collider->GetWorldPosition();
	direction.y = 0.f;
	float dist = direction.Length();
	Vector3::Normalize(&direction);
	float radiusSum = other->collider->GetRadius() + collider->GetRadius();
	if (radiusSum > dist)
	{
		float pushDist = radiusSum - dist;
		transform->position += direction * pushDist;
	}
}

void Unit::SetTeam(Team _team)
{
	team = _team;
}

void Unit::SetAttackTarget(Unit* _target)
{
	attackTarget = _target;
}

void Unit::SetHP(float _max)
{
	maxHp = _max;
	hp = _max;
}

void Unit::SetMP(float _max)
{
	maxMp = _max;
	mp = _max;
}

void Unit::SetHPRegen(float _per5Sec)
{
	hpRegen = _per5Sec;
}

void Unit::SetMPRegen(float _per5Sec)
{
	mpRegen = _per5Sec;
}

void Unit::SetAttackDamage(float _damage)
{
	attackDamage = _damage;
}

void Unit::SetAttackPerSec(float _attackPerSec)
{
	attackPerSec = _attackPerSec;
	anim->SetSpeed(UnitState::ATTACK1, _attackPerSec);
	anim->SetSpeed(UnitState::ATTACK2, _attackPerSec);
	anim->SetSpeed(UnitState::ATTACK3, _attackPerSec);
	anim->SetSpeed(UnitState::ATTACK4, _attackPerSec);
	anim->SetSpeed(UnitState::CRITICAL, _attackPerSec);
}

void Unit::SetAttackRange(float _range)
{
	attackRange = _range;
}

void Unit::SetAbilityPower(float _ap)
{
	abilityPower = _ap;
}

void Unit::SetMovementSpeed(float _speed)
{
	movementSpeed = _speed;
	agent->SetSpeed(_speed);
}

void Unit::SetArmor(float _armor)
{
	armor = _armor;
}

void Unit::SetMagicResistance(float _magicResist)
{
	magicResistance = _magicResist;
}

void Unit::SetCriticalPer(float _percent)
{
	criticalPer = _percent;
}

void Unit::SetCooldownReduction(float _cdr)
{
	cooldownReduction = _cdr;
}

void Unit::TakeDamage(float _damage)
{
	hp -= _damage;
	if (hp <= 0.f)
	{
		Die();
	}
}

void Unit::SetID(INT _id)
{
	unitID = _id;
}

bool Unit::IsDead()
{
	return isDead;
}

INT Unit::GetID()
{
	return unitID;
}

float Unit::GetHP()
{
	return hp;
}

float Unit::GetMP()
{
	return mp;
}

float Unit::GetMaxHP()
{
	return maxHp;
}

float Unit::GetMaxMP()
{
	return maxMp;
}

float Unit::GetAttackDamage()
{
	return attackDamage;
}

float Unit::GetAttackRange()
{
	return attackRange;
}

float Unit::GetAbilityPower()
{
	return abilityPower;
}

float Unit::GetAttackPerSec()
{
	return attackPerSec;
}

float Unit::GetMovementSpeed()
{
	return movementSpeed;
}

float Unit::GetArmor()
{
	return armor;
}

float Unit::GetMagicResistance()
{
	return magicResistance;
}

float Unit::GetCriticalPer()
{
	return criticalPer;
}

float Unit::GetCooldownReduction()
{
	return cooldownReduction;
}
