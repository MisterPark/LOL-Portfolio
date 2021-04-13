#pragma once
#include "Item.h"
#include "Stat.h"
#include "Skill.h"
#include "json/json.hpp"

NLOHMANN_JSON_SERIALIZE_ENUM(StatType, {
	{ StatType::END,                     nullptr },
	{ StatType::AttackDamage,            "AttackDamage" },
	{ StatType::AbilityPower,            "AbilityPower" },
	{ StatType::ArmorPenetration,        "ArmorPenetration" },
	{ StatType::ArmorPenetrationPercent, "ArmorPenetrationPercent" },
	{ StatType::MagicPenetration,        "MagicPenetration" },
	{ StatType::MagicPenetrationPercent, "MagicPenetrationPercent" },
	{ StatType::Armor,                   "Armor" },
	{ StatType::MagicResistance,         "MagicResistance" },
	{ StatType::MovementSpeed,           "MovementSpeed" },
	{ StatType::CriticlaChance,          "CriticlaChance" },
	{ StatType::AbilityHaste,            "AbilityHaste" },
	{ StatType::Health,                  "Health" },
	{ StatType::Mana,                    "Mana" },
	{ StatType::Experience,              "Experience" },
	{ StatType::MaxHealth,               "MaxHealth" },
	{ StatType::MaxMana,                 "MaxMana" },
	{ StatType::MaxExperience,           "MaxExperience" },
	{ StatType::HealthRegen,             "HealthRegen" },
	{ StatType::ManaRegen,               "ManaRegen" },
	{ StatType::Shield,                  "Shield" },
	{ StatType::LifeSteal,               "LifeSteal" },
	{ StatType::PhysicalVamp,            "PhysicalVamp" },
	{ StatType::OmniVamp,                "OmniVamp" },
	{ StatType::HealAndShieldPower,      "HealAndShieldPower" },
	{ StatType::Tenacity,                "Tenacity" },
	{ StatType::SlowResist,              "SlowResist" },
	{ StatType::Range,                   "Range" },
	{ StatType::AttackSpeed,             "AttackSpeed" },
	{ StatType::DamageReduction,         "DamageReduction" },
	})

NLOHMANN_JSON_SERIALIZE_ENUM(ItemType, {
	{ ItemType::End,       nullptr },
	{ ItemType::Starter,   "Starter" },
	{ ItemType::Basic,     "Basic" },
	{ ItemType::Epic,      "Epic" },
	{ ItemType::Legendary, "Legendary" },
	{ ItemType::Mythic,    "Mythic" },
	{ ItemType::Consume,   "Consume" },
	{ ItemType::Trinkets,  "Trinkets" },
	{ ItemType::Boots,     "Boots" },
	})

class ItemManager
{
	ItemManager();
	virtual ~ItemManager();

public:
	static ItemManager* GetInstance();
	static void Destroy();
	
	void Initialize();

	Item* GetItem(UINT itemID);
	map<UINT, Item*> GetItemList();
	Skill* GetItemSkill(const std::wstring& _skillname);

private:
	HRESULT LoadItemInfo();
	HRESULT AddItem(const nlohmann::json& jsonItemInfo);
	void DeleteListAll();

	map<UINT, Item*> items; // Item ID, Item
	map<std::wstring, Skill*> skills;
};