#pragma once

#define INVENTORY_MAX	7

#include "Item.h"
#include "Slot.h"

class Item;
class Inventory
{
public:
	Inventory();
	~Inventory();

public:
	void DeleteAll();
	Item* Push(int _id);
	bool Pop(int _idx);
	
	Item* GetItem(int _idx);
	int SellItem(int _idx);

private:
	Slot slots[INVENTORY_MAX];
	
};

