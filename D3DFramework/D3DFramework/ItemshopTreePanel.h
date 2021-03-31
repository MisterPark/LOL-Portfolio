#pragma once
#include "Panel.h"

class OutlinedSlot;
class Label;
class Item;
class ItemshopSlot;

class ItemshopTreePanel : public Panel
{
public:
	explicit ItemshopTreePanel();
	ItemshopTreePanel(Vector2 _pos);
	virtual ~ItemshopTreePanel();

public:
	virtual void Update();
	virtual void Show();
	virtual void Hide();
	virtual void Show(bool _visible);

	void SetRootItem(Item* _item);

private:
	Item* Rootitem = nullptr;

	ItemshopSlot* rootSlot = nullptr;

};