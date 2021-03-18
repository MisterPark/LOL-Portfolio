#pragma once
using namespace Engine;


enum class ItemType
{
	None, // 다른거 전부
	Consume, // 소모
	Boots, // 
	End
};

class Item
{
public:
	virtual void Update();
	virtual void Use() = 0;

	ItemType type = ItemType::None;
	UINT id;
	UINT price = 0;
	std::wstring icon;
	std::wstring name;
	std::wstring desc;
	list<UINT> itemParentId;
	list<UINT> itemChildId;
	
};

