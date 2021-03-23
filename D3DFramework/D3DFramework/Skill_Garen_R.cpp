#include "stdafx.h"
#include "Skill_Garen_R.h"
#include "Buff.h"
#include "Collider.h"
#include "SphereCollider.h"
#include "Unit.h"
#include "DamageCalc_Basic.h"
#include "DamageCalc_LostHpPercent.h"
#include "Champion.h"

Skill_Garen_R::Skill_Garen_R(Unit* _hostUnit)
{
	maxLevel = 3;
	coolTime = 2.f;
	duration = 1.f;
	host = _hostUnit;

	Add_DamageCalc(DamageCalc_Basic::CreateCalc(DamageKind::TrueDamage));
	Add_DamageCalc(DamageCalc_LostHpPercent::CreateCalc(0.1f, DamageKind::TrueDamage));
}

Skill_Garen_R::~Skill_Garen_R()
{
}

void Skill_Garen_R::Start()
{
	if (coolTimeTick > 0.f)
		return;


	Skill::Start();

	Ray ray = Camera::main->ScreenPointToRay(Input::GetMousePosition());

	RaycastHit info;
	int unitMask = LayerMask::GetMask(Layer::Unit);
	if (Physics::Raycast(ray, &info, INFINITY, unitMask))
	{
		Unit* target = (Unit*)info.collider->gameObject;
		if (target->team != host->team && !target->IsDead())
		{
			target->SetLastAttacker(host);
			float finalDamage = baseDamage;
			Calc_FinalDamage(&finalDamage, host->stat, target->stat);
			target->TakeDamage(finalDamage);
		}
	}


	coolTimeTick = coolTime;

}

void Skill_Garen_R::Passive()
{
	if (coolTimeTick > 0.f) {
		coolTimeTick -= Time::DeltaTime();
	}

}

void Skill_Garen_R::Active()
{
	//if (!active)
		//return;

	if (tick <= 0.f) {
		End();
		return;
	}

	host->agent->Stop();
	host->SetState(State::R);
	//사용효과
	tick -= Time::DeltaTime();
}


void Skill_Garen_R::End()
{
	Skill::End();
}
