#pragma once
using namespace Engine;
#include "Stat.h"
#include "Skill_Item.h"
#include "Buff_Item.h"

enum class ItemType
{
	Starter, // 시작
	Basic, // 기본
	Epic, // 서사
	Legendary, // 전설
	Mythic, // 신화
	Consume, // 소모
	Trinkets, // 장신구
	Boots, // 신발
	End
};

class Item
{
public:
	explicit Item();
	explicit Item(
		const UINT& _id,
		const std::wstring& _tag,
		const std::wstring& _name,
		const ItemType& _itemType,
		const UINT& _price,
		const std::wstring& _desc,
		const map<StatType, int>& _stats,
		const map<std::wstring, void*>& _effects,
		const list<std::wstring>& _recipes
	);
	~Item();

public:
	static Item* Create(
		const UINT& _id,
		const std::wstring& _tag,
		const std::wstring& _name,
		const ItemType& _itemType,
		const UINT& _price,
		const std::wstring& _desc,
		const map<StatType, int>& _stats,
		const map<std::wstring, void*>& _effects,
		const list<std::wstring>& _recipes
		);

	void Passive();
	void Active();

	int Sell();
	void Destroy();
	Buff_Item* StatBuffSetting(Unit* _host);
	//void Use();

	UINT GetId();
	std::wstring GetIcon();
	std::wstring GetName();
	ItemType GetType();
	UINT GetPrice();
	std::wstring GetDesc();

private:
	UINT id;
	std::wstring icon;
	std::wstring name;
	ItemType type = ItemType::End;
	UINT price = 0; // 조합 후 최종 가격
	std::wstring desc;

public: 
	map<StatType, int> stats;
	map<std::wstring, void*> effects; // 어떻게 할지 생각해봐야함
	list<std::wstring> recipes; // id로 변경하기
	//list<UINT> itemParentId;
	//list<UINT> itemChildId;
	list<Skill_Item*> skillList;
	Buff_Item* buffItemStat = nullptr; // 팔때 제거해줘야함
};

