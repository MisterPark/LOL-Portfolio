#pragma once
#include "Panel.h"
#include "Stat.h"
#include "Unit.h"
#include "Inventory.h"

class Champion;
class Engine::UI;
class Label;
class OutlinedSlot;
class Button;

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

	void SetTarget(Champion* _target);
	void PlayerPanel_OnClick(GameObject* sender, MouseEventArg* arg);
	void SellSelectedItem();
	void UnselectInventorySlot();
	int GetSelectedItemIdx();

public:
	int screenW = 1280;
	int screenH = 720;

private:
	Champion* champion = nullptr;

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
	Label* hpRegenLabel = nullptr;
	float hpBarBackRatio = 1.f;

	// mp bar
	Label* mpLabel = nullptr;
	Label* mpRegenLabel = nullptr;
	Engine::UI* mpBar = nullptr;
	Engine::UI* mpBarMarker = nullptr;

	// stat
	map<UINT, StatType> statNum = {
		{0, StatType::AttackDamage    },
		{1, StatType::AbilityPower    },
		{2, StatType::Armor           },
		{3, StatType::MagicResistance },
		{4, StatType::AttackSpeed     },
		{5, StatType::AbilityHaste    },
		{6, StatType::CriticlaChance  },
		{7, StatType::MovementSpeed   }
	};
	Label* statLabel[8] = { nullptr, };

	// Level
	Label* levelLabel = nullptr;

	// EXP Bar
	UI* expBar = nullptr;

	// Spell
	map<UINT, SkillIndex> spellNum = {
		{0, SkillIndex::Q },
		{1, SkillIndex::W },
		{2, SkillIndex::E },
		{3, SkillIndex::R }
	};
	UINT spellPoint = 0;
	int spellLevelMax[4] = { 5, 5, 5, 3 };
	UINT spellLevel[4] = { 0, 0, 0, 0 };

	OutlinedSlot* slotSpell[4] = { nullptr, };
	Label* SpellTimeLabel[4] = { nullptr, };
	vector<vector<UI*>> spellLevelUI;
	Button* spellLevelUpButton[4] = { nullptr, };

	Label* spellPointLabel = nullptr;

	// Passive
	OutlinedSlot* slotPassive = nullptr;
	OutlinedSlot* slotSummoner1 = nullptr;
	OutlinedSlot* slotSummoner2 = nullptr;

	// Item
	OutlinedSlot* slotItem[INVENTORY_MAX] = { nullptr, };
	UI*           slotItemSelected[INVENTORY_MAX] = { nullptr, };
	OutlinedSlot* slotRecall = nullptr;
	Button* itemshopBtn = nullptr;
	int selectedItemIdx = -1;
	void ClickInventorySlot(GameObject* sender, MouseEventArg* args);

	// Event
	static void ClickStatButton();
};

