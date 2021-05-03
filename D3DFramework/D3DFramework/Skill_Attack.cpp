#include "stdafx.h"
#include "Skill_Attack.h"
#include "Unit.h"


Skill_Attack::Skill_Attack(Unit* _hostUnit)
{
	maxLevel = 1;
	level = 1;
	host = _hostUnit;
	coolTime = 1.f / host->stat->GetValue(StatType::AttackSpeed);
	coolTimeTick = coolTime;
	range = host->stat->GetValue(StatType::Range);
}

Skill_Attack::~Skill_Attack()
{
}
 
void Skill_Attack::Start()
{
	coolTime = 1.f / host->stat->GetValue(StatType::AttackSpeed);
	duration = 1.f / host->stat->GetValue(StatType::AttackSpeed);
	range = host->stat->GetValue(StatType::Range);
	
	if (GetCooltime() > 0.f) return;
	Skill::Start();

	host->OnAttackBegin();
}

void Skill_Attack::Passive()
{
	if (coolTimeTick < coolTime)
	{
		coolTimeTick += Time::DeltaTime();
	}
}

void Skill_Attack::Active()
{
	range = host->stat->GetValue(StatType::Range);

	Unit* attackTarget = host->GetAttackTarget();
	if (attackTarget != nullptr)
	{
		lastTargetPosition = attackTarget->transform->position;
	}
	float dt = Time::DeltaTime();
	

	Vector3 direction = lastTargetPosition - host->transform->position;
	host->agent->Stop();
	host->LookRotation(direction.Normalized());
	host->SetState(host->attackState);

	tick += dt;
	duration = 1.f / host->stat->GetValue(StatType::AttackSpeed);
	if (tick > duration)
	{
		
		End();
		return;
	}
	float damageDelay = duration * 0.3f;
	if (tick > damageDelay)
	{
		if (host->attackFlag == false)
		{
			host->attackFlag = true;

			if (attackTarget == nullptr) return;

			attackTarget->SetLastAttacker(host);
			float finalDamage = host->stat->GetValue(StatType::AttackDamage);
			host->Calc_FinalDamage(&finalDamage, host->stat, attackTarget->stat);
			attackTarget->OnDamaged(host, this, &finalDamage);
			host->OnHit(attackTarget, this);
			attackTarget->TakeDamage(finalDamage);
			// 피격정보 저장
			Unit::HitInfo info;
			info.damageSum += finalDamage;
			info.unit = host;

			auto iter = attackTarget->hitList.begin();
			auto end = attackTarget->hitList.end();
			for (; iter != end;)
			{
				if ((*iter).unit == host)
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

	//if (host->anim->IsFrameEnd() && host->anim->GetIndexByState((int)host->attackState) == host->anim->GetCurrentAnimation())
	//{
	//	End();
	//	return;
	//}
}

void Skill_Attack::End()
{
	active = false;
	tick = 0.f;
	host->OnAttackEnd();
	host->attackFlag = false;
	if(host->attackState > State::ATTACK4)
		host->attackState = State::ATTACK1;
}

void Skill_Attack::AttackCancelToAttack()
{
	Start();
	tick = 0.f;
}

void Skill_Attack::Cancel()
{
	End();
}
