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

	attackIndicator = (Indicator*)SceneManager::GetCurrentScene()->CreateObject<Indicator>(Layer::Indicator);
	//attackIndicator = new Indicator;
	attackIndicator->SetTarget(this);

	stat = (Stat*)AddComponent<Stat>(L"Stat");
	SetAttackPerSec(0.625f);

	// TODO : 행동트리
	bt = (BehaviorTree*)AddComponent<BehaviorTree>(L"BehaviorTree");
	
	SelectorNode* root = new SelectorNode();
	bt->SetRoot(root);
	
	ConditionNode<Unit>* deathCondition = new ConditionNode<Unit>();
	deathCondition->SetCondition(this, &Unit::IsDead);
	root->AddChild(deathCondition);

	ActionNode<Unit>* deathAction = new ActionNode<Unit>();
	deathAction->SetAction(this, &Unit::DeadAction);
	deathCondition->SetChild(deathAction);

	//
	ConditionNode<Skill>* skillCondition = new ConditionNode<Skill>();
	skillCondition->SetCondition(skillList[(int)SkillIndex::Q], &Skill::IsActive);
	root->AddChild(skillCondition);

	ActionNode<Skill>* skillQAction = new ActionNode<Skill>();
	skillQAction->SetAction(skillList[(int)SkillIndex::Q], &Skill::Active);
	skillCondition->SetChild(skillQAction);
	//

	ConditionNode<NavMeshAgent>* moveCondition = new ConditionNode<NavMeshAgent>();
	moveCondition->SetCondition(agent, &NavMeshAgent::IsPathRemain);
	root->AddChild(moveCondition);

	ActionNode<Unit>* moveAction = new ActionNode<Unit>();
	moveAction->SetAction(this, &Unit::MoveAction);
	moveCondition->SetChild(moveAction);

	SelectorNode* attackSelector = new SelectorNode();
	root->AddChild(attackSelector);

	ConditionNode<Unit>* attackCondition = new ConditionNode<Unit>();
	attackCondition->SetCondition(this, &Unit::HasAttackTarget);
	attackSelector->AddChild(attackCondition);

	ActionNode<Unit>* attackAction = new ActionNode<Unit>();
	attackAction->SetAction(this, &Unit::AttackAction);
	attackCondition->SetChild(attackAction);

	ConditionNode<Unit>* countAttackCondition = new ConditionNode<Unit>();
	countAttackCondition->SetCondition(this, &Unit::HasLastAttacker);
	attackSelector->AddChild(countAttackCondition);

	ActionNode<Unit>* countAttackAction = new ActionNode<Unit>();
	countAttackAction->SetAction(this, &Unit::CounterAttack);
	countAttackCondition->SetChild(countAttackAction);
	
	ActionNode<Unit>* idleAction = new ActionNode<Unit>();
	idleAction->SetAction(this, &Unit::IdleAction);
	root->AddChild(idleAction);
}

Unit::~Unit()
{
	unitList.remove(this);

	anim = nullptr;
	agent = nullptr;
	stat = nullptr;
	bt = nullptr;
	attackIndicator = nullptr;

	for (auto calc : damageCalcList)
	{
		delete calc;
	}
	for (int i = 0; i < (int)SkillIndex::END; i++)
	{
		if (skillList[i] == nullptr)
			continue;
		delete skillList[i];
	}
}

void Unit::Initialize()
{
}

void Unit::Release()
{
}

void Unit::Update()
{
	
	UpdateLastAttacker();

	GameObject::Update();

	attackIndicator->Update();

	for (int i = 0; i < (int)SkillIndex::END; i++)
	{
		if (skillList[i] == NULL)
			continue;
		skillList[i]->Passive();
	}
}


void Unit::UpdateLastAttacker()
{
	lastAttackTick += Time::DeltaTime();
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
	chaseTick += Time::DeltaTime();
	if (chaseTick > chaseDelay)
	{
		chaseTick = 0.f;
		agent->SetStoppingDistance((*stat)[StatType::Range]);
		SetDestination(_target);
	}
}

void Unit::Attack(Unit* target)
{
	if (target == nullptr) return;

	attackTarget = target;
	
}

void Unit::OnAttackBegin()
{
	beginAttackFlag = true;
}

void Unit::OnAttackEnd()
{
	beginAttackFlag = false;
	oldAttackState = attackState;

	if (attackState == State::ATTACK1)
	{
		attackState = State::ATTACK2;
	}
	else if (attackState == State::ATTACK2)
	{
		attackState = State::ATTACK1;
	}
}

void Unit::Spell1()
{
	skillList[(int)SkillIndex::Q]->Start();
}

void Unit::Spell2()
{
	skillList[(int)SkillIndex::W]->Start();
}

void Unit::Spell3()
{
	skillList[(int)SkillIndex::E]->Start();
}

void Unit::Spell4()
{
	skillList[(int)SkillIndex::R]->Start();
}

void Unit::Die()
{
	isDead = true;
	collider->enable = false;
}

void Unit::DeadAction()
{
	SetState(State::DEATH);
	attackTarget = nullptr;
	UINT curAnim = anim->GetCurrentAnimation();
	UINT deathAnim = anim->GetIndexByState((int)State::DEATH);
	if (curAnim == deathAnim && anim->IsFrameEnd())
	{
		anim->Stop();
	}
	agent->Stop();
}

void Unit::AttackAction()
{
	float dt = Time::DeltaTime();

	if (anim->IsFrameEnd() && anim->GetIndexByState((int)attackState) == anim->GetCurrentAnimation())
	{
		OnAttackEnd();
	}

	if (attackTarget->IsDead())
	{
		attackTarget = nullptr;
		return;
	}

	Vector3 direction = attackTarget->transform->position - transform->position;
	float dist = direction.Length();
	float targetRadius = attackTarget->collider->GetRadius();
	if (dist <= (*stat)[StatType::Range] + targetRadius) // 공격 거리 이내
	{
		agent->Stop();
		LookRotation(direction.Normalized());
		SetState(attackState);
		if (beginAttackFlag == false)
		{
			OnAttackBegin();
		}

		attackTick += dt;
		float attackDelay = 1.f / (*stat)[StatType::AttackSpeed];
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

				attackTarget->SetLastAttacker(this);
				float finalDamage = (*stat)[StatType::AttackDamage];
				Calc_FinalDamage(&finalDamage, stat, attackTarget->stat);
				attackTarget->TakeDamage(finalDamage);
				
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

void Unit::CounterAttack()
{
	attackTarget = lastAttacker;
}

void Unit::IdleAction()
{
	SetState(State::IDLE1);
	attackTick = 0.f;
	isDamaged = false;
}

void Unit::MoveAction()
{
	SetState(State::RUN);
}

void Unit::SkillQAction()
{
}

void Unit::SkillWAction()
{
}

void Unit::SkillEAction()
{
}

void Unit::SkillRAction()
{
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

void Unit::SetState(State _state)
{
	state = _state;
	anim->SetState((int)_state);
}

State Unit::GetState()
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

void Unit::SetAttackPerSec(float _attackPerSec)
{
	anim->SetSpeed((int)State::ATTACK1, _attackPerSec);
	anim->SetSpeed((int)State::ATTACK2, _attackPerSec);
	anim->SetSpeed((int)State::ATTACK3, _attackPerSec);
	anim->SetSpeed((int)State::ATTACK4, _attackPerSec);
	anim->SetSpeed((int)State::CRITICAL, _attackPerSec);
}

void Unit::SetLastAttacker(Unit* _attacker)
{
	lastAttacker = _attacker;
	lastAttackTick = 0.f;
}

void Unit::TakeDamage(float _damage)
{
	stat->DecreaseBaseValue(StatType::Health, _damage);
}

void Unit::SetID(INT _id)
{
	unitID = _id;
}

bool Unit::IsDead()
{
	return isDead;
}

bool Unit::HasAttackTarget()
{
	return (attackTarget != nullptr);
}

bool Unit::HasLastAttacker()
{
	return (lastAttacker != nullptr);
}

void Unit::Calc_FinalDamage(float* _damage, Stat* _myStat, Stat* _targetStat)
{
	for (auto& calc : damageCalcList)
	{
		calc->Calc(_damage, _myStat, _targetStat);
	}
}

INT Unit::GetID()
{
	return unitID;
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

