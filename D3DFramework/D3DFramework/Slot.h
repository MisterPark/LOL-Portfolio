#pragma once
class Item;

class Slot
{
public:
	Slot();
	~Slot();

	Item* Push(UINT _id);
	bool Pop();
	void Delete();

public:
	Item* item = nullptr;
	int num = 0;

};
