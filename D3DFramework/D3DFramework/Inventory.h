#pragma once

#define INVENTORY_MAX	7

#include "Item.h"
#include "Slot.h"

class Inventory
{
public:
	Inventory();
	~Inventory();

public:
	bool Push(Item* item);
	bool Pop(int _idx);
	
	Item* GetItem(int _idx);
	void ItemSell(int _idx);

private:
	Slot slots[INVENTORY_MAX];
	
};

