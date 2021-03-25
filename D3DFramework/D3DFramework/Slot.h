#pragma once
class Item;

class Slot
{
public:
	Slot();
	~Slot();

public:
	Item* item = nullptr;
	int num = 0;

};
