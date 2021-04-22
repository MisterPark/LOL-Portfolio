#pragma once
#include "IComponent.h"

class Buff;
class Unit;

enum class StatType {
	AttackDamage, AbilityPower, // 공격력, 주문력
	ArmorPenetration, ArmorPenetrationPercent, // 방어구 관통력
	MagicPenetration, MagicPenetrationPercent, // 마법 관통력
	Armor,MagicResistance, // 방어력, 마법 저항력
	MovementSpeed, CriticlaChance, CriticlaDamage, // 이동 속도, 치명타 확률, 치명타 피해량
	AbilityHaste, // 스킬 가속
	Health,Mana, Experience, // 체력, 마나, 경험치
	MaxHealth, MaxMana, MaxExperience, // 최대 체력, 최대 마나, 최대 경험치
	HealthRegen, ManaRegen, // 체력 회복량, 마나 회복량
	Shield, // 쉴드량
	LifeSteal, PhysicalVamp, OmniVamp, // 생명력 흡수, 물리 피해 흡혈, 모든 피해 흡혈
	HealAndShieldPower, // 회복 및 보호막 효과
	Tenacity, SlowResist, // 강인함, 둔화 저항
	Range,AttackSpeed, // 사정거리, 1초당 공격속도(횟수)
	DamageReduction,
	Level, // 레벨
	SkillPoint,
	MinionKilled,
	Gold,
	Bounty, // 현상금
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
	list<Buff*>* GetBuffList() { return &buffList; }
	//Buff* GetBuff(Buff::BuffName _name);
	void AddBuff(Buff* buff);
	void RemoveBuff(Buff* buff);

	template<class T>
	void RemoveBuff();

private:
	Unit* unit = nullptr;
	float baseValues[MaxOfEnum<StatType>()] = {};
	float additional[MaxOfEnum<StatType>()] = {};
	float percent[MaxOfEnum<StatType>()] = {};
	float finalValues[MaxOfEnum<StatType>()] = {};

	list<Buff*> buffList;
};

template<class T>
inline void Stat::RemoveBuff()
{
	for (auto& buff : buffList)
	{
		if (dynamic_cast<T*>(buff) == nullptr) continue;
		buff->tick = buff->duration;
	}
}
