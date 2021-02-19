#pragma once
#include "Panel.h"


class Champion;
class Label;
class PKH::UI;
class OutlinedSlot;

class PlayerInfoPanel : public Panel
{
public:
	PlayerInfoPanel();
	virtual ~PlayerInfoPanel();

public:
	static PlayerInfoPanel* GetInstance();
	static void DestroyInstance();

	// UI을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Release() override;

	virtual void Update() override;

	//void RenderStat();
	//void RenderMini();
	//void RenderBar();

	void SetTarget(Champion* _target);

public:

	int screenW = 1280;
	int screenH = 720;
private:
	PKH::UI* statPanel = nullptr;
	PKH::UI* mainPanel = nullptr;
	PKH::UI* invenPanel = nullptr;
	PKH::UI* faceBorder = nullptr;
	PKH::UI* facePanel = nullptr;
	Label* hpLabel = nullptr;
	Label* mpLabel = nullptr;

	Label* statLabel[8] = { nullptr, };
	Label* level = nullptr;
	Label* gold = nullptr;

	OutlinedSlot* slotSpell1 = nullptr;
	OutlinedSlot* slotSpell2 = nullptr;
	OutlinedSlot* slotSpell3 = nullptr;
	OutlinedSlot* slotSpell4 = nullptr;
	OutlinedSlot* slotPassive = nullptr;
	OutlinedSlot* slotSummoner1 = nullptr;
	OutlinedSlot* slotSummoner2 = nullptr;

	Champion* champion = nullptr;

	static void ClickStatButton();
};

