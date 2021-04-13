#pragma once
#include "Panel.h"
class ItemshopSlot;
class ItemshopTreePanel;
class Champion;
class Button;

class ItemshopPanel : public Panel
{
public:
	ItemshopPanel();
	virtual ~ItemshopPanel();

public:
	static ItemshopPanel* GetInstance();
	static void DestroyInstance();

	virtual void Update();

	virtual void Show();
	virtual void Hide();

	static void ToggleVisible(GameObject* sender, MouseEventArg* arg);
	static void Close();

	void SetTarget(Champion* _target);

	void HideItemShopPanel(GameObject* sender, MouseEventArg* args);
	void BuyItem(UINT _id);
	
private:
	Champion* champion = nullptr;

	Button* sellButton = nullptr;

	// leftslot
	vector<ItemshopSlot*> slots;
	ItemshopSlot* selectedSlot = nullptr; // 참조용
	
	// rightslot
	ItemshopTreePanel* treePanel = nullptr;
	UI* selectItemIcon = nullptr;
	Label* selectItemNameLabel = nullptr;
	Label* selectItemPriceLabel = nullptr;
	Label* selectItemDescLabel = nullptr;

	// etc
	Label* currentGoldLabel = nullptr;

	void SetSelectItem(ItemshopSlot* _slot);
	void SelectItemList(GameObject* sender, MouseEventArg* args);
	void BuyItem(GameObject* sender, MouseEventArg* args);
	void SellItem(GameObject* sender, MouseEventArg* args);

	void ShowTooltipItem(GameObject* sender, MouseEventArg* args);
	void HideTooltipItem(GameObject* sender, MouseEventArg* args);
};