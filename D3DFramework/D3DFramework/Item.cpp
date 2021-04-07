#include "stdafx.h"
#include "Item.h"
#include "Unit.h"

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
	for (auto& skill : skillList) {
		delete skill;
	}
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

int Item::Sell() {
	Destroy();
	return price * 0.6f;
}

void Item::Destroy()
{
	buffItemStat->duration = 0.f;
	for (auto& skill : skillList) {
		delete skill;
	}
}

Buff_Item* Item::StatBuffSetting(Unit* _host)
{
	Buff_Item* buffItem = new Buff_Item(_host);//reductionValue);
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

