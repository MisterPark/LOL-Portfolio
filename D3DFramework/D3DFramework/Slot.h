#pragma once
class Item;

class Slot
{
public:
	Slot();
	~Slot();

	bool Pop();

public:
	Item* item = nullptr;
	int num = 0;

};
