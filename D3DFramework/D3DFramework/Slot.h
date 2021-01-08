#pragma once
#include "UI.h"

class Item;

class Slot : public UI
{
public:
	Slot();
	~Slot();

	virtual void Initialize() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render() override;

	virtual void OnHover();
	virtual void OnLeave();
	virtual void OnClick();
	virtual void OnRButtonDown();

	void Use();

	Item* GetItem();
	Item* SetItem(Item* inItem);
	
private:
	Item* item = nullptr;
public:
	Vector3 position;

};

