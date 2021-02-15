#include "stdafx.h"
#include "Unit.h"
#include "SphereCollider.h"
#include "NavMeshAgent.h"
#include "Indicator.h"

list<Unit*> Unit::unitList;

Unit::Unit()
{
	unitList.push_back(this);

	anim = (Animation*)AddComponent<Animation>(L"Animation");
	collider = (SphereCollider*)AddComponent<SphereCollider>(L"SphereCollider");
	collider->SetRadius(0.5f);
	collider->center = { 0.f,1.f,0.f };

	agent = (NavMeshAgent*)AddComponent< NavMeshAgent>(L"NavMeshAgent");

	attackIndicator = (Indicator*)ObjectManager::GetInstance()->CreateObject<Indicator>(Layer::Indicator);
	//attackIndicator = new Indicator;
	attackIndicator->SetTarget(this);

	stat = (UnitStat*)AddComponent<UnitStat>(L"UnitStat");
	SetAttackPerSec(0.625f);
}

Unit::~Unit()
{
	unitList.remove(this);

	anim = nullptr;
	agent = nullptr;
	stat = nullptr;

	//attackIndicator->SetTarget(nullptr);
	//attackIndicator->Destroy();
	//delete attackIndicator;
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
	UpdateLastAttacker();

	GameObject::Update();

	attackIndicator->Update();
}


void Unit::UpdateState()
{
	float dt = TimeManager::DeltaTime();
	
	if (isDead)
	{
		SetState(UnitState::DEATH);
		attackTarget = nullptr;
		UINT curAnim = anim->GetCurrentAnimation();
		UINT deathAnim = anim->GetIndexByState((int)UnitState::DEATH);
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
		float targetRadius = attackTarget->collider->GetRadius();
		if (dist <= attackRange +targetRadius) // 공격 거리 이내
		{
			agent->Stop();
			LookRotation(direction.Normalized());
			SetState(attackState);

			attackTick += dt;
			float attackDelay = 1.f / attackPerSec;
			if (attackTick > attackDelay)
			{
				attackTick = 0.f;
				isDamaged = false;
			}
			float damageDelay = attackDelay * 0.2f;
			if (attackTick > damageDelay)
			{
				if (isDamaged == false)
				{
					isDamaged = true;
					Network* net = Network::GetInstance();
					
					if (net->isMultiGame)
					{
						if (net->number == unitID)
						{
							ReqDamage(unitID, attackTarget->GetID(), stat->attackDamage.GetValue());
						}
						else if (unitID > 9 && net->number == 0)
						{
							ReqDamage(unitID, attackTarget->GetID(), stat->attackDamage.GetValue());
						}
					}
					else
					{
						attackTarget->SetLastAttacker(this);
						attackTarget->TakeDamage(stat->attackDamage.GetValue());
					}
				}
			}
			
		}
		else
		{
			attackTick = 0.f;
			isDamaged = false;
			Chase(attackTarget->transform->position);
			
		}
	}
	else
	{
		attackTick = 0.f;
		isDamaged = false;
	}
	
}

void Unit::UpdateLastAttacker()
{
	lastAttackTick += TimeManager::DeltaTime();
	if (lastAttackTick > lastAttackDuration)
	{
		lastAttackTick = 0.f;
		lastAttacker = nullptr;
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

void Unit::Chase(Vector3 _target)
{
	chaseTick += TimeManager::DeltaTime();
	if (chaseTick > chaseDelay)
	{
		chaseTick = 0.f;
		agent->SetStoppingDistance(attackRange);
		SetDestination(_target);
	}
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

void Unit::SetState(UnitState _state)
{
	state = _state;
	anim->SetState((int)_state);
}

UnitState Unit::GetState()
{
	return state;
}

void Unit::SetTeam(Team _team)
{
	team = _team;
}

void Unit::SetAttackTarget(Unit* _target)
{
	attackTarget = _target;
}

Unit* Unit::GetAttackTarget()
{
	return attackTarget;
}

void Unit::SetHP(float _max)
{
	stat->maxHp = _max;
	stat->hp = _max;
}

void Unit::SetMP(float _max)
{
	stat->maxMp = _max;
	stat->mp = _max;
}

void Unit::SetHPRegen(float _per5Sec)
{
	stat->hpRegen = _per5Sec;
}

void Unit::SetMPRegen(float _per5Sec)
{
	stat->mpRegen = _per5Sec;
}

void Unit::SetAttackDamage(float _damage)
{
	stat->attackDamage = _damage;
}

void Unit::SetAttackPerSec(float _attackPerSec)
{
	attackPerSec = _attackPerSec;
	anim->SetSpeed((int)UnitState::ATTACK1, _attackPerSec);
	anim->SetSpeed((int)UnitState::ATTACK2, _attackPerSec);
	anim->SetSpeed((int)UnitState::ATTACK3, _attackPerSec);
	anim->SetSpeed((int)UnitState::ATTACK4, _attackPerSec);
	anim->SetSpeed((int)UnitState::CRITICAL, _attackPerSec);
}

void Unit::SetAttackRange(float _range)
{
	attackRange = _range;
}

void Unit::SetAbilityPower(float _ap)
{
	stat->abilityPower = _ap;
}

void Unit::SetMovementSpeed(float _speed)
{
	stat->movementSpeed = _speed;
	agent->SetSpeed(_speed);
}

void Unit::SetArmor(float _armor)
{
	stat->armor = _armor;
}

void Unit::SetMagicResistance(float _magicResist)
{
	stat->magicResistance = _magicResist;
}

void Unit::SetCriticalPer(float _percent)
{
	stat->criticalPer = _percent;
}

void Unit::SetCooldownReduction(float _cdr)
{
	stat->cooldownReduction = _cdr;
}

void Unit::SetLastAttacker(Unit* _attacker)
{
	lastAttacker = _attacker;
	lastAttackTick = 0.f;
}

void Unit::TakeDamage(float _damage)
{
	stat->hp -= _damage;
	if (stat->hp <= 0.f)
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
	return stat->hp.GetValue();
}

float Unit::GetMP()
{
	return stat->mp.GetValue();
}

float Unit::GetMaxHP()
{
	return stat->maxHp.GetValue();
}

float Unit::GetMaxMP()
{
	return stat->maxMp.GetValue();
}

float Unit::GetAttackDamage()
{
	return stat->attackDamage.baseValue;
}

float Unit::GetAttackRange()
{
	return attackRange;
}

float Unit::GetAbilityPower()
{
	return stat->abilityPower.GetValue();
}

float Unit::GetAttackPerSec()
{
	return attackPerSec;
}

float Unit::GetMovementSpeed()
{
	return stat->movementSpeed.GetValue();
}

float Unit::GetArmor()
{
	return stat->armor.GetValue();
}

float Unit::GetMagicResistance()
{
	return stat->magicResistance.GetValue();
}

float Unit::GetCriticalPer()
{
	return stat->criticalPer.GetValue();
}

float Unit::GetCooldownReduction()
{
	return stat->cooldownReduction.GetValue();
}

Unit* Unit::GetLastAttacker()
{
	return lastAttacker;
}

Unit* Unit::GetNearestEnemy(Vector3 point, float radius)
{
	Unit* target = nullptr;
	float targetDist = radius;

	for (Unit* iter : unitList)
	{
		if (iter->IsDead()) continue;
		if (team != iter->team)
		{
			Vector3 to = iter->transform->position - point;
			float dist = to.Length();
			if (dist < targetDist)
			{
				target = iter;
				targetDist = dist;
			}
		}
	}

	return target;
}

void Unit::ReqMove(Vector3 _dest, bool _noSearch)
{
	list<Vector3> path;
	int pathCount = 0;

	CPacket* pack = new CPacket();
	*pack << (WORD)GAME_REQ_MOVE << this->GetID();

	if (_noSearch)
	{
		pathCount = 1;
		*pack << pathCount << _dest.x << _dest.y << _dest.z;

	}
	else
	{
		bool res = agent->Search(_dest, &path);
		if (res)
		{
			pathCount = path.size();
			*pack << pathCount;

			for (auto iter : path)
			{
				*pack << iter.x << iter.y << iter.z;
			}


		}
		else
		{
			pathCount = 1;
			*pack << pathCount << _dest.x << _dest.y << _dest.z;
		}
	}
	Network::SendPacket(pack);
	delete pack;
	Debug::PrintLine("[Debug] ReqMove 요청 / 경유지 : %d", pathCount);
}

void Unit::ReqAttack(Unit* _target)
{
	INT unitID = _target->GetID();
	CPacket* pack = new CPacket();

	*pack << (WORD)GAME_REQ_ATTACK << this->GetID() << unitID;

	Network::SendPacket(pack);
	delete pack;
	Debug::PrintLine("[Debug] ReqAttack 요청 / 공격자ID : %d / 타겟ID : %d", this->GetID(), unitID);
}

void Unit::ReqDamage(INT _attackerID, INT _targetID, float _damage)
{
	CPacket* pack = new CPacket();

	*pack << (WORD)GAME_REQ_DAMAGE << _attackerID << _targetID << _damage;

	Network::SendPacket(pack);
	delete pack;
	Debug::PrintLine("[Debug] ReqDamage 요청 / 공격자ID : %d / 타겟ID : %d", _attackerID, _targetID);
}
