#pragma once
#include "Panel.h"
#include "Stat.h"

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
	float hp;
	float hpMax;

	// mp bar
	Label* mpLabel = nullptr;
	Label* mpRegenLabel = nullptr;
	Engine::UI* mpBar = nullptr;
	Engine::UI* mpBarMarker = nullptr;
	float mp;
	float mpMax;

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
	Label* gold = nullptr;

	OutlinedSlot* slotSpell1 = nullptr;
	OutlinedSlot* slotSpell2 = nullptr;
	OutlinedSlot* slotSpell3 = nullptr;
	OutlinedSlot* slotSpell4 = nullptr;
	OutlinedSlot* slotPassive = nullptr;
	OutlinedSlot* slotSummoner1 = nullptr;
	OutlinedSlot* slotSummoner2 = nullptr;

	static const int spell1LevelMax = 5;
	static const int spell2LevelMax = 5;
	static const int spell3LevelMax = 5;
	static const int spell4LevelMax = 3;

	UI* spell1LevelUI[spell1LevelMax] = { nullptr, };
	UI* spell2LevelUI[spell2LevelMax] = { nullptr, };
	UI* spell3LevelUI[spell3LevelMax] = { nullptr, };
	UI* spell4LevelUI[spell4LevelMax] = { nullptr, };

	UINT spell1Level = 0;
	UINT spell2Level = 0;
	UINT spell3Level = 0;
	UINT spell4Level = 0;

	static void ClickStatButton();
};

