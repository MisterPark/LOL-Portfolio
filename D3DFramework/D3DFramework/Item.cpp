﻿#include "stdafx.h"
#include "Item.h"
#include "Unit.h"

Item::Item()
{
}

Item::Item(const UINT& _id, const std::wstring& _tag, const std::wstring& _name, const ItemType& _itemType, const UINT& _price, const std::wstring& _desc, const list<Buff::Node>& _stats, const list<std::wstring>& _effects, const list<std::wstring>& _recipes)
{
	id = _id;
	icon = _tag;
	name = _name;
	type = _itemType;
	price = _price;
	desc = _desc;
	stats = _stats;
	effects = _effects;
	recipes = _recipes;

}

Item::~Item()
{
	Destroy();
}

Item* Item::Create(const UINT& _id, const std::wstring& _tag, const std::wstring& _name, const ItemType& _itemType, const UINT& _price, const std::wstring& _desc, const list<Buff::Node>& _stats, const list<std::wstring>& _effects, const list<std::wstring>& _recipes)
{
	return new Item(_id, _tag, _name, _itemType, _price, _desc, _stats, _effects, _recipes);
}

Item* Item::Clone()
{
	Item* item = new Item(
		this->id,
		this->icon,
		this->name,
		this->type,
		this->price,
		this->desc,
		this->stats,
		this->effects,
		this->recipes
	);

	return item;
}

void Item::Passive()
{
	//for (auto skill : skillList) {
	//	skill->Passive();
	//}
}

void Item::Active()
{
	//for (auto skill : skillList) {
	//	skill->Active();
	//}
}

void Item::Destroy()
{
	stats.clear();
	effects.clear();
	recipes.clear();

	if (buffItemStat) {
		buffItemStat->duration = 0.f;
	}
	//
	if (skillList.size() == 0) return;
	Unit* host = skillList.front()->GetHost();

	for (auto& skill : skillList) {
		for (auto iter = host->itemSkillList.begin(); iter != host->itemSkillList.end(); iter++)
		{
			if ((*iter)->GetSkillName() == skill->GetSkillName()) {
				if ((*iter)->overlapCount == 1) {
					delete (*iter);
					iter = host->itemSkillList.erase(iter);
				}
				else
					(*iter)->overlapCount--;
				break;
			}
		}
	}

	skillList.clear();
	//
}

bool Item::SetTarget(Unit* _host)
{
	SetSkillList(_host);
	StatBuffSetting(_host);

	return true;
}

void Item::SetSkillList(Unit* _host)
{
	for (auto effect : effects)
	{
		Skill* skill = ItemManager::GetInstance()->GetItemSkill(effect);
		if (skill == nullptr) continue;

		Skill* newSkill = skill->Clone();
		newSkill->SetTarget(_host);
		skillList.push_back(_host->AddItemSkill(newSkill));
	}
}

Buff_ItemStat* Item::StatBuffSetting(Unit* _host)
{
	if (stats.size() <= 0) return nullptr;

	Buff_ItemStat* buffItem = new Buff_ItemStat(_host);//reductionValue);

	for (const auto& stat : stats)
	{
		buffItem->AddModifier(stat.type, stat.value, stat.isPercent);
	}
	
	_host->stat->AddBuff(buffItem);
	buffItemStat = buffItem;
	return buffItem;
}

UINT Item::GetId() { return id; }
std::wstring Item::GetIcon() { return icon; }
std::wstring Item::GetName() { return name; }
ItemType Item::GetType() { return type; }
UINT Item::GetPrice() { return price; }
std::wstring Item::GetDesc() { return desc; }

