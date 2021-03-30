#pragma once
//#include "Panel.h"
#include "Button.h"

class OutlinedSlot;
class Label;
class Item;

class ItemshopSlot : public Button
{
public:
	ItemshopSlot(Vector2 _pos, Item* _item);
	virtual ~ItemshopSlot();

public:
	virtual void Update();
	virtual void OnClick();
	virtual void Show();
	virtual void Hide();
	virtual void Show(bool _visible);

	Item* GetItem();
	UINT GetItemId();
	void SetItem(Item* _item);

	bool selected = false;

private:
	UI* selectUI = nullptr;
	OutlinedSlot* slot = nullptr;
	Label* price = nullptr;
	Item* item = nullptr;

};