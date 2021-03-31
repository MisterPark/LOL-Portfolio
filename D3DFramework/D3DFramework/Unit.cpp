#include "stdafx.h"
#include "Unit.h"
#include "SphereCollider.h"
#include "NavMeshAgent.h"
#include "Indicator.h"
#include "Buff.h"
#include "Monster.h"
#include "Garen.h"
#include "TargetingSkill.h"
#include "Skill_Attack.h"

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

	//행동트리
	bt = (BehaviorTree*)AddComponent<BehaviorTree>(L"BehaviorTree");
	
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
	UpdateSpawn();
	UpdateHit();

	GameObject::Update();

	//attackIndicator->Update();

	for (int i = 0; i < (int)SkillIndex::END; i++)
	{
		if (skillList[i] == NULL)
			continue;
		skillList[i]->Passive();
	}

	for (int i = 0; i < INVENTORY_MAX; i++)
	{
		Item* item = inventory.GetItem(i);
		if (item == nullptr)
			continue;
		item->Passive();
	}

	if (dynamic_cast<Garen*>(this))
	{
		if (skillList[(int)SkillIndex::Attack]->IsActive())
		{
			Debug::PrintLine("Active");
		}
		else
		{
			Debug::PrintLine("None");
		}
	}
	
}


void Unit::UpdateHit()
{
	float dt = Time::DeltaTime();
	// 마지막 피격자 업데이트
	lastAttackTick += dt;
	if (lastAttackTick > lastAttackDuration)
	{
		lastAttackTick = 0.f;
		lastAttacker = nullptr;
	}
	// 피격 트리거 업데이트
	if (oldHitFlag == true)
	{
		hitFlag = false;
	}
	if (hitFlag != oldHitFlag)
	{
		oldHitFlag = hitFlag;
	}
	// 피격자 리스트 업데이트
	auto iter = hitList.begin();
	auto end = hitList.end();
	for (;iter!=end;)
	{
		(*iter).tick += dt;
		if ((*iter).tick >= (*iter).duration)
		{
			iter = hitList.erase(iter);
			continue;
		}

		++iter;
	}
}

void Unit::UpdateSpawn()
{
	float dt = Time::DeltaTime();
	if (spawnFlag)
	{
		spawnTick += dt;
		if (spawnTick > spawnDelay)
		{
			spawnFlag = false;
			spawnTick = 0.f;
			attackTarget = nullptr;
			lastAttacker = nullptr;
			collider->enable = true;
			float maxHP = stat->GetValue(StatType::MaxHealth);
			float maxMP = stat->GetValue(StatType::MaxMana);
			stat->SetBaseValue(StatType::Health,maxHP);
			stat->SetBaseValue(StatType::Mana, maxMP);
			transform->position = spawnPosition;
			isDead = false;
			anim->Resume();
			Show();

		}
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

void Unit::ChaseTarget()
{
	if (attackTarget == nullptr) return;
	if (nextSkill == nullptr) return;
	chaseTick += Time::DeltaTime();
	if (chaseTick > chaseDelay)
	{
		chaseTick = 0.f;
		agent->SetStoppingDistance(nextSkill->GetRange()-0.1f);
		SetDestination(attackTarget->transform->position);
	}
}

void Unit::OnAttackBegin()
{
	beginAttackFlag = true;
	anim->SetSpeed((int)State::ATTACK1, (*stat)[StatType::AttackSpeed]);
	anim->SetSpeed((int)State::ATTACK2, (*stat)[StatType::AttackSpeed]);
	anim->SetSpeed((int)State::ATTACK3, (*stat)[StatType::AttackSpeed]);
	anim->SetSpeed((int)State::ATTACK4, (*stat)[StatType::AttackSpeed]);
	anim->SetSpeed((int)State::CRITICAL, (*stat)[StatType::AttackSpeed]);
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

void Unit::Attack()
{
	if (skillList[(int)SkillIndex::Attack] == nullptr) return;
	skillList[(int)SkillIndex::Attack]->Use();
}

void Unit::Spell1()
{
	if (skillList[(int)SkillIndex::Q] == nullptr) return;
	skillList[(int)SkillIndex::Q]->Use();
}

void Unit::Spell2()
{
	if (skillList[(int)SkillIndex::W] == nullptr) return;
	skillList[(int)SkillIndex::W]->Use();
}

void Unit::Spell3()
{
	if (skillList[(int)SkillIndex::E] == nullptr) return;
	skillList[(int)SkillIndex::E]->Use();
}

void Unit::Spell4()
{
	if (skillList[(int)SkillIndex::R] == nullptr) return;
	skillList[(int)SkillIndex::R]->Use();
}

void Unit::Spell5()
{
	if (skillList[(int)SkillIndex::D] == nullptr) return;
	skillList[(int)SkillIndex::D]->Use();
}

void Unit::Spell6()
{
	if (skillList[(int)SkillIndex::F] == nullptr) return;
	skillList[(int)SkillIndex::F]->Use();
}

void Unit::Die()
{
	isDead = true;
	for (auto& hitInfo : hitList)
	{
		hitInfo.unit->OnKilled(this);
	}
}

void Unit::OnKilled(Unit* target)
{
	if (dynamic_cast<Monster*>(target) != nullptr)
	{
		float exp = target->stat->GetBaseValue(StatType::Experience);
		stat->IncreaseBaseValue(StatType::Experience, exp);
		
	}

}

void Unit::DeadAction()
{
	SetState(State::DEATH);
	attackTarget = nullptr;
	collider->enable = false;
	UINT curAnim = anim->GetCurrentAnimation();
	UINT deathAnim = anim->GetIndexByState((int)State::DEATH);
	if (curAnim == deathAnim && anim->IsFrameEnd())
	{
		anim->Stop();
		Hide();
	}
	agent->Stop();
	if (spawnFlag == false)
	{
		Respawn();
	}
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
			attackFlag = false;
		}
		float damageDelay = attackDelay * 0.15f;
		if (attackTick > damageDelay)
		{
			if (attackFlag == false)
			{
				attackFlag = true;

				attackTarget->SetLastAttacker(this);
				float finalDamage = (*stat)[StatType::AttackDamage];
				Calc_FinalDamage(&finalDamage, stat, attackTarget->stat);
				attackTarget->TakeDamage(finalDamage);
				// 피격정보 저장
				HitInfo info;
				info.damageSum += finalDamage;
				info.unit = this;

				auto iter = attackTarget->hitList.begin();
				auto end = attackTarget->hitList.end();
				for (; iter != end;)
				{
					if ((*iter).unit == this)
					{
						info.damageSum += (*iter).damageSum;
						iter = attackTarget->hitList.erase(iter);
						break;
					}
					++iter;
				}

				attackTarget->hitList.push_back(info);
			}
		}

	}
	else
	{
		attackTick = 0.f;
		attackFlag = false;
		Chase(attackTarget->transform->position);

	}
}

void Unit::CounterAttack()
{
	attackTarget = lastAttacker;
	nextSkill = skillList[(int)SkillIndex::Attack];
}

void Unit::IdleAction()
{
	SetState(State::IDLE1);
	attackTick = 0.f;
	attackFlag = false;
}

void Unit::MoveAction()
{
	SetState(moveState);
	attackTick = 0.f;
	attackFlag = false;
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

void Unit::Respawn()
{
	spawnFlag = true;
	spawnTick = 0.f;
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
Team Unit::GetTeam()
{
	return team;
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

void Unit::SetAttackPoint(Vector3 _pos)
{
	this->attackPoint = _pos;
}

void Unit::SetNextSkill(Skill* _skill)
{
	this->nextSkill = _skill;
}

void Unit::SetNextSkillReady(Skill* _skill)
{
	this->nextSkillReady = _skill;
}

void Unit::TakeNextSkill()
{
	nextSkill = nextSkillReady;
}

void Unit::TakeDamage(float _damage)
{
	_damage = DecreaseShieldBuff(_damage);

	stat->DecreaseBaseValue(StatType::Health, _damage);
	hitFlag = true;
}

float Unit::DecreaseShieldBuff(float _damage)
{
	for (auto& buff : *stat->GetBuffList())
	{
		for (auto& modi : buff->modifiers) {
			if (modi.type == StatType::Shield) {
				if (modi.value > _damage) {
					modi.value -= _damage;
					return 0.f; // 실드에 데미지가 다 막힘.
				}
				else {
					_damage -= modi.value;
					modi.value = 0.f;
					buff->tick = INFINITY; // 실드를 다 써서 실드버프삭제
					continue;
				}
			}
		}
	}
	return _damage; // 실드가 데미지를 다 못막아서 남은 데미지를 반환
}

void Unit::SetID(INT _id)
{
	unitID = _id;
}

Vector3 Unit::GetSpawnPosition()
{
	return spawnPosition;
}

void Unit::SetSpawnPosition(Vector3 _spawnPos)
{
	this->spawnPosition = _spawnPos;
}

float Unit::GetRemainingRespawnTime()
{
	return (spawnDelay - spawnTick);
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

bool Unit::HasNextSkill()
{
	return (nextSkill != nullptr);
}

void Unit::StartNextSkill()
{
	this->nextSkill->Start();
	this->nextSkill = nullptr;
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

void Unit::SkillLevelUp(SkillIndex skillIndex)
{
	if (stat->GetBaseValue(StatType::SkillPoint) <= 0.f)
		return;
	Skill* skill = skillList[(int)skillIndex];
	if (skill->GetLevel() == skill->GetMaxLevel())
		return;
	// TODO:: 챔피언레벨업이 가능해지면 주석 풀것
	//if ((float)(skill->GetLevel() * 2 + 1) > stat->GetBaseValue(StatType::Level))
	//	return;
	stat->DecreaseBaseValue(StatType::SkillPoint, 1.f);
	skill->AddLevel();
}

Skill_Attack* Unit::GetSkillAttack()
{
	return dynamic_cast<Skill_Attack*>(skillList[(int)SkillIndex::Attack]);
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

bool Unit::AddItem(Item* _item)
{
	if (_item == nullptr) return false;

	return inventory.Push(_item);
}

bool Unit::BuyItem(Item* _item)
{
	if (_item == nullptr) return false;

	// 금액 부족
	int gold = (int)stat->GetBaseValue(StatType::Gold) - _item->price;
	if (gold < 0) return false;
	
	// 인벤토리 푸쉬
	if (!inventory.Push(_item)) return false;

	// 골드 소모
	stat->SetBaseValue(StatType::Gold, (float)gold);

	return true;
}

void Unit::SellItem(int _idx)
{
	Item* item = inventory.GetItem(_idx);
	if (item == nullptr) return;
	float price = item->price * 0.7f;

	bool success = inventory.Pop(_idx);
	if (!success) return;

	if (price < 0.f) return;
	
	stat->SetBaseValue(StatType::Gold, stat->GetBaseValue(StatType::Gold) + price);
}

