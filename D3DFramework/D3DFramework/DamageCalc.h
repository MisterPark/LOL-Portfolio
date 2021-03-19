#pragma once
#include "Stat.h"

enum class CalcKind
{
	Basic, MaxHp_Per, CurrentHp_Per, LostHp_Per, END
};
enum class DamageKind
{
	AD, AP, TrueDamage, END
};

namespace Engine
{
	class DamageCalc
	{
	protected:
		DamageCalc();

	public:
		~DamageCalc();
		virtual void Calc(float* _damage, Stat* _myStat, Stat* _targetStat) = 0;

	protected:
		float Calc_Defense(float _damage, Stat* _myStat, Stat* _targetStat);
	protected:
		float value = 0.f;
		DamageKind damageKind = DamageKind::END;
	};
}

