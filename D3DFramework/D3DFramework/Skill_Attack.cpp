#include "stdafx.h"
#include "Skill_Attack.h"
#include "Unit.h"


Skill_Attack::Skill_Attack(Unit* _hostUnit)
{
	maxLevel = 1;
	level = 1;
	host = _hostUnit;
	coolTime = 1.f / host->stat->GetValue(StatType::AttackSpeed);
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
	
	if (coolTimeTick > 0.f) return;
	Skill::Start();

	host->OnAttackBegin();
}

void Skill_Attack::Passive()
{
	if (coolTimeTick > 0.f) {
		coolTimeTick -= Time::DeltaTime();
	}
}

void Skill_Attack::Active()
{
	if (host->attackTarget == nullptr)
	{
		End();
		return;
	}
	else
	{
		if (host->attackTarget->IsDead())
		{
			host->attackTarget = nullptr;
			End();
			return;
		}
	}
	float dt = Time::DeltaTime();
	

	Vector3 direction = host->attackTarget->transform->position - host->transform->position;
	host->agent->Stop();
	host->LookRotation(direction.Normalized());
	host->SetState(host->attackState);

	tick -= dt;
	float attackDelay = 1.f / host->stat->GetValue(StatType::AttackSpeed);
	if (tick <= 0.f)
	{
		End();
		return;
	}
	float damageDelay = duration * 0.15f;
	if (duration - tick > damageDelay)
	{
		if (host->attackFlag == false)
		{
			host->attackFlag = true;

			host->attackTarget->SetLastAttacker(host);
			float finalDamage = host->stat->GetValue(StatType::AttackDamage);
			host->Calc_FinalDamage(&finalDamage, host->stat, host->attackTarget->stat);
			host->attackTarget->TakeDamage(finalDamage);
			// 피격정보 저장
			Unit::HitInfo info;
			info.damageSum += finalDamage;
			info.unit = host;

			auto iter = host->attackTarget->hitList.begin();
			auto end = host->attackTarget->hitList.end();
			for (; iter != end;)
			{
				if ((*iter).unit == host)
				{
					info.damageSum += (*iter).damageSum;
					iter = host->attackTarget->hitList.erase(iter);
					break;
				}
				++iter;
			}

			host->attackTarget->hitList.push_back(info);
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
	active = true;
	tick = duration;
	host->OnAttackEnd();
	host->attackFlag = false;
}
