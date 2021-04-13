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
		const list<Buff::Node>& _stats,
		const list<std::wstring>& _effects,
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
		const list<Buff::Node>& _stats,
		const list<std::wstring>& _effects,
		const list<std::wstring>& _recipes
		);

public:
	Item* Clone();

public:
	void Passive();
	void Active();

	void Destroy();

	UINT GetId();
	std::wstring GetIcon();
	std::wstring GetName();
	ItemType GetType();
	UINT GetPrice();
	std::wstring GetDesc();

public:
	bool SetTarget(Unit* _host);
private:
	void SetSkillList(Unit* _host);
	Buff_Item* StatBuffSetting(Unit* _host);

private:
	UINT id;
	std::wstring icon;
	std::wstring name;
	ItemType type = ItemType::End;
	UINT price = 0; // 조합 후 최종 가격
	std::wstring desc;

public: 
	list<Buff::Node> stats; // 스텟 버프 데이터
	list<std::wstring> effects; // 스킬 데이터
	list<std::wstring> recipes; // id로 변경하기
	//list<UINT> itemParentId;
	//list<UINT> itemChildId;
	list<Skill_Item*> skillList;
	Buff_Item* buffItemStat = nullptr; // Stat에서 제거해줌
};

