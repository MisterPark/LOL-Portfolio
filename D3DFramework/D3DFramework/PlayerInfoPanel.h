#pragma once
#include "Panel.h"
#include "Stat.h"

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
	Label* level = nullptr;

	// Spell
	static const int spell1LevelMax = 5;
	static const int spell2LevelMax = 5;
	static const int spell3LevelMax = 5;
	static const int spell4LevelMax = 3;
	UINT spellPoint = 0;
	UINT spell1Level = 0;
	UINT spell2Level = 0;
	UINT spell3Level = 0;
	UINT spell4Level = 0;

	OutlinedSlot* slotSpell1 = nullptr;
	OutlinedSlot* slotSpell2 = nullptr;
	OutlinedSlot* slotSpell3 = nullptr;
	OutlinedSlot* slotSpell4 = nullptr;
	Label* slotSpell1Label = nullptr;
	Label* slotSpell2Label = nullptr;
	Label* slotSpell3Label = nullptr;
	Label* slotSpell4Label = nullptr;

	UI* spell1LevelUI[spell1LevelMax] = { nullptr, };
	UI* spell2LevelUI[spell2LevelMax] = { nullptr, };
	UI* spell3LevelUI[spell3LevelMax] = { nullptr, };
	UI* spell4LevelUI[spell4LevelMax] = { nullptr, };

	Button* spell1LevelUpButton = nullptr;
	Button* spell2LevelUpButton = nullptr;
	Button* spell3LevelUpButton = nullptr;
	Button* spell4LevelUpButton = nullptr;

	Label* spellPointLabel = nullptr;

	// Passive
	OutlinedSlot* slotPassive = nullptr;
	OutlinedSlot* slotSummoner1 = nullptr;
	OutlinedSlot* slotSummoner2 = nullptr;

	// Item
	Button* itemshopBtn = nullptr;

	// Event
	static void ClickStatButton();
};

