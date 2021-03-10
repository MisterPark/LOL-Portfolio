#pragma once
#include "Panel.h"


class Champion;
class Label;
class Engine::UI;
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

	void SetHP(float _value, float _maxValue);
	void SetMP(float _value, float _maxValue);

	void SetTarget(Champion* _target);
	void PlayerPanel_OnClick(GameObject* sender, MouseEventArg* arg);
public:

	int screenW = 1280;
	int screenH = 720;
private:
	Engine::UI* statPanel = nullptr;
	Engine::UI* mainPanel = nullptr;
	Engine::UI* invenPanel = nullptr;
	Engine::UI* faceBorder = nullptr;
	Engine::UI* facePanel = nullptr;

	// hp bar
	Engine::UI* hpBarBack = nullptr;
	Engine::UI* hpBar = nullptr;
	Engine::UI* hpBarMarker = nullptr;
	Label* hpLabel = nullptr;
	float hpBarBackRatio = 1.f;
	float hp;
	float hpMax;

	// mp bar
	Label* mpLabel = nullptr;
	Engine::UI* mpBar = nullptr;
	Engine::UI* mpBarMarker = nullptr;
	float mp;
	float mpMax;

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

