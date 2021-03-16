#include "stdafx.h"
#include "Skill_Garen_R.h"
#include "Buff.h"
#include "Collider.h"
#include "Unit.h"
#include "DamageCalc_Basic.h"
#include "DamageCalc_LostHpPercent.h"

Skill_Garen_R::Skill_Garen_R(Unit* _hostUnit)
{
	coolTime_Init = 2.f;
	duration = 0.f;
	hostUnit = _hostUnit;

	Add_DamageCalc(DamageCalc_Basic::CreateCalc(0.f, true));
	Add_DamageCalc(DamageCalc_LostHpPercent::CreateCalc(0.1f, true));
}

Skill_Garen_R::~Skill_Garen_R()
{
}

void Skill_Garen_R::Start()
{
	Skill::Start();

	Ray ray = Camera::main->ScreenPointToRay(Input::GetMousePosition());

	RaycastHit info;
	int unitMask = LayerMask::GetMask(Layer::Unit, Layer::Building);
	if (Physics::Raycast(ray, &info, INFINITY, unitMask))
	{
		Unit* target = (Unit*)info.collider->gameObject;
		if (target->team != hostUnit->team && !target->IsDead())
		{
			target->SetLastAttacker(hostUnit);
			float finalDamage = baseDamage;
			Calc_FinalDamage(&finalDamage, hostUnit->stat, target->stat);
			target->TakeDamage(finalDamage);
		}
	}


	coolTime = coolTime_Init;

}

void Skill_Garen_R::Passive()
{
	if (coolTime > 0.f) {
		coolTime -= Time::DeltaTime();
	}

}

void Skill_Garen_R::Active()
{
	//if (!active)
		//return;

	if (duration <= 0.f) {
		End();
		return;
	}

	//사용효과
	duration -= Time::DeltaTime();
}


void Skill_Garen_R::End()
{
	Skill::End();
}
