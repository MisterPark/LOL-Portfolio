﻿#include "stdafx.h"
#include "Item.h"

Item::Item()
{
}

Item::Item(const UINT& _id, const std::wstring& _tag, const std::wstring& _name, const ItemType& _itemType, const UINT& _price, const std::wstring& _desc, const map<StatType, int>& _stats, const map<std::wstring, void*>& _effects, const list<std::wstring>& _recipes)
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
	for (auto& skill : skillList)
		delete skill;
}

Item* Item::Create(const UINT& _id, const std::wstring& _tag, const std::wstring& _name, const ItemType& _itemType, const UINT& _price, const std::wstring& _desc, const map<StatType, int>& _stats, const map<std::wstring, void*>& _effects, const list<std::wstring>& _recipes)
{
	return new Item(_id, _tag, _name, _itemType, _price, _desc, _stats, _effects, _recipes);
}

void Item::Passive()
{
	for (auto skill : skillList) {
		skill->Passive();
	}
}

void Item::Active()
{
	for (auto skill : skillList) {
		skill->Active();
	}
}

