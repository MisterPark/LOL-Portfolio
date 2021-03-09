#pragma once
#define dfSLOT_COL_COUNT 5
#define dfSLOT_ROW_COUNT 3
#define dfMAX_SLOT_COUNT (dfSLOT_COL_COUNT * dfSLOT_ROW_COUNT)

#include "Item.h"
#include"Slot.h"

class Inventory
{
private:
	Inventory();
	~Inventory();

public:
	static Inventory* GetInstance();
	static void Destroy();

	static void Show();
	static void Show(bool on);
	static void Hide();

	static void Update();

	static bool Push(Item* item);

	static int GetItemCount(ItemType _type);
	static void RemoveItem(ItemType _type, int count);

private:
	void UpdateUI();

private:
	Slot slots[dfMAX_SLOT_COUNT] = {  };
	
public:
	Vector3 position;
	bool enable = false;
	bool visible = false;

};

