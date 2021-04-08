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
	void DeleteAll();
	bool Push(int _id);
	bool Pop(int _idx);
	
	Item* GetItem(int _idx);

private:
	Slot slots[INVENTORY_MAX];
	
};

