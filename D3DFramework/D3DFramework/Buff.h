#pragma once
#include "Stat.h"
class Unit;

class Buff
{
public:
	enum class BuffName{
		Ghost,
		GarenPHealthRegen, GarenQAttack, GarenQHaste, GarenWReduction, Buff_GarenWPassive, GarenWShield, GarenEDamage, GarenEArmorDec,
		END
	};
	struct Node
	{
		StatType type;
		float value;
		bool isPercent;
	};
	Buff(Unit* _host, float _duration);
	virtual ~Buff();

	virtual void Update();

	void AddModifier(StatType _type, float _value, bool _isPercent = false);

public:
	Unit* host = nullptr;
	list<Buff::Node> modifiers;
	float tick = 0.f;
	float duration = 0.f;
	BuffName buffName = BuffName::END;
	int overlapCount = 1;
	int maxOverlapCount = 1;
};

