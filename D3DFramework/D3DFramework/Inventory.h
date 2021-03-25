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

public:
	Slot slots[INVENTORY_MAX];
	
};

