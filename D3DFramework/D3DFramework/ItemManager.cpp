#include "stdafx.h"
#include "ItemManager.h"
#include "json/UnicodeHelper.h"
#include <fstream>
#include "Skill_Item_Cleave.h"
#include "Skill_Item_Dreadnought.h"
#include "Skill_Item_ManaCharge.h"
#include "Skill_Item_SpellBlade.h"
#include "Skill_Item_Thorns.h"
#include "Skill_Item_WitchsFocus.h"

ItemManager* pItemManager = nullptr;

ItemManager::ItemManager()
{
	skills.emplace(L"쪼개기", new Skill_Item_Cleave(nullptr));
	skills.emplace(L"침몰시키는 자", new Skill_Item_Dreadnought(nullptr));
	skills.emplace(L"마나 충전", new Skill_Item_ManaCharge(nullptr));
	skills.emplace(L"주문 검", new Skill_Item_SpellBlade(nullptr));
	skills.emplace(L"가시", new Skill_Item_Thorns(nullptr));
	skills.emplace(L"마법사의 길", new Skill_Item_WitchsFocus(nullptr));
}

ItemManager::~ItemManager()
{
	DeleteListAll();
}

ItemManager* ItemManager::GetInstance()
{
	if (pItemManager == nullptr)
	{
		pItemManager = new ItemManager();
	}
	return pItemManager;
}

void ItemManager::Destroy()
{
	if (pItemManager)
	{
		delete pItemManager;
		pItemManager = nullptr;
	}
}

void ItemManager::Initialize()
{
	LoadItemInfo();
}

Item* ItemManager::GetItem(UINT itemID)
{
	return items.find(itemID)->second;
}

map<UINT, Item*> ItemManager::GetItemList()
{
	return items;
}

Skill_Item* ItemManager::GetItemSkill(const std::wstring& _skillname)
{
	auto iter = skills.find(_skillname);
	if (skills.end() == iter) return nullptr;

	return iter->second;
}

HRESULT ItemManager::LoadItemInfo()
{
	std::wstring jsonFilePath{ L"./Data/Item/iteminfo.json" };
	std::ifstream fis;

	// 파일 오픈
	fis.open(jsonFilePath);
	if (!fis.is_open()) {
		MessageBox(g_hwnd, L"iteminfo.json 불러오기 실패", nullptr, MB_OK);
		return E_FAIL;
	}

	nlohmann::json jsonFile{ nlohmann::json::parse(fis) };


	// 아이템 데이터 추가
	for (auto it : jsonFile)
	{
		if (AddItem(it) == E_FAIL) {
			fis.close();
			return E_FAIL;
		}
	}

	fis.close();

	return S_OK;
}

HRESULT ItemManager::AddItem(const nlohmann::json& jsonItemInfo)
{
// id
	UINT id = jsonItemInfo[u8"id"];

// tag
	std::wstring tag = ConvertUTF8ToWide(jsonItemInfo[u8"tag"]);

// name
	std::wstring name = ConvertUTF8ToWide(jsonItemInfo[u8"name"]);

// type
	ItemType itemType = jsonItemInfo[u8"type"].get<ItemType>();
	if (itemType == ItemType::End)
		return E_FAIL;

// price
	UINT price = jsonItemInfo[u8"price"];

// desc
	std::wstring desc = ConvertUTF8ToWide(jsonItemInfo[u8"desc"]);
	
// stat
	list<Buff::Node> stats;
	for (auto statData : jsonItemInfo[u8"stat"])
	{
		StatType type = statData[u8"type"].get<StatType>();
		if (type == StatType::END)
			return E_FAIL;

		float value = statData[u8"value"];

		bool ispercent = statData[u8"ispercent"];

		Buff::Node stat(type, value, ispercent);
		stats.push_back(stat);
	}

// effect
	list<std::wstring> effects;
	for (auto effectData : jsonItemInfo[u8"effect"])
	{
		std::wstring effectName = ConvertUTF8ToWide(effectData);
		effects.push_back(effectName);
	}

// recipe
	list<std::wstring> recipes;
	for (auto recipeData : jsonItemInfo[u8"recipe"])
	{
		std::wstring recipeName = ConvertUTF8ToWide(recipeData);
		recipes.push_back(recipeName);
	}

// Add
	Item* item = Item::Create(id, tag, name, itemType, price, desc, stats, effects, recipes);
	if (item == nullptr)
		return E_FAIL;

	items.emplace(id, item);

	return S_OK;
}

void ItemManager::DeleteListAll()
{
	for (auto item : items)
	{
		delete item.second;
	}
	items.clear();

	for (auto skill : skills)
	{
		delete skill.second;
	}
	skills.clear();
}
