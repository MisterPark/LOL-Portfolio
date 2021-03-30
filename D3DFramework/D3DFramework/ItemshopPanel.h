#pragma once
#include "Panel.h"
class ItemshopSlot;
class ItemshopTreePanel;
class Champion;

class ItemshopPanel : public Panel
{
public:
	ItemshopPanel();
	virtual ~ItemshopPanel();

public:
	static ItemshopPanel* GetInstance();
	static void DestroyInstance();

	virtual void Update();

	//virtual void Show();
	virtual void Hide();

	static void ToggleVisible(GameObject* sender, MouseEventArg* arg);
	static void Close();

	void SetTarget(Champion* _target);

	void HideItemShopPanel(GameObject* sender, MouseEventArg* args);
	
private:
	Champion* champion = nullptr;

	// Buy
	void BuyItem(GameObject* sender, MouseEventArg* args);

	// leftslot
	vector<ItemshopSlot*> slots;
	ItemshopSlot* selectedSlot = nullptr;
	
	// rightslot
	ItemshopTreePanel* treePanel = nullptr;

	void SetSelectItem(ItemshopSlot* _slot);
	void SelectItemList(GameObject* sender, MouseEventArg* args);
};