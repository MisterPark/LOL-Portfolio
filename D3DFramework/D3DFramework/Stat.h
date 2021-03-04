#pragma once
#include "IComponent.h"

class Unit;
class Buff;

enum class StatType{
	AttackDamage, AbilityPower,
	ArmorPenetration,ArmorPenetrationPercent,
	MagicPenetration,MagicPenetrationPercent,
	Armor,MagicResistance,
	MovementSpeed,CriticlaChance,
	AbilityHaste,
	Health,Mana, Experience,
	MaxHealth, MaxMana, MaxExperience,
	HealthRegen,ManaRegen,
	Shield,
	LifeSteal, PhysicalVamp, OmniVamp,
	HealAndShieldPower, // 회복 및 보호막효과
	Tenacity, SlowResist, // 강인함, 둔화 저항
	Range,AttackSpeed, // 사거리, 1초당 공격속도(횟수)
	Level,
	END
};

class Stat : public IComponent
{
public:
    explicit Stat(GameObject* owner);
    explicit Stat(const Stat& rhs);
    virtual ~Stat();
    virtual IComponent* Clone() override;

	virtual void PreUpdate() override;
	virtual void Update() override;
	virtual void PostUpdate() override;

	float operator[](StatType type);

	void SetBaseValue(StatType _type, float _value);
	float GetBaseValue(StatType _type);
	float IncreaseBaseValue(StatType _type, float _modifier);
	float DecreaseBaseValue(StatType _type, float _modifier);

	float GetValue(StatType _type);

	void AddBuff(Buff* buff);

private:
	Unit* unit = nullptr;
	float baseValues[MaxOfEnum<StatType>()] = {};
	float additional[MaxOfEnum<StatType>()] = {};
	float percent[MaxOfEnum<StatType>()] = {};

	list<Buff*> buffList;
};

