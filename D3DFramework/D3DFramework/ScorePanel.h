#pragma once
#include "Panel.h"
#include "Unit.h"

class Champion;

enum class Dragon
{
	WIND,	// 바람
	FIRE,	// 화염
	EARTH,	// 대지
	WATER,	// 바다
	BREAK,	// X
	END
};

extern std::wstring dragonCountTex[(UINT)Dragon::END];
extern std::wstring dragonSoulTex1[(UINT)Dragon::END];
extern std::wstring dragonSoulTex2[(UINT)Dragon::END];

class ScorePanel :
	public Panel
{
public:
	ScorePanel();
	virtual ~ScorePanel();
public:
	static ScorePanel* GetInstance();
	static void DestroyInstance();

	virtual void Update() override;

	void AddChampion(Champion* _champ, bool _isPlayer = false);
	
	// 용
	void AddDragon(Dragon _dragon, Team _team);
	void SetDragonSoul(Dragon _dragon); // 3용 이후 용 결정될 때
	void SetDragonSoulBuf(); // 4용 버프 적용될 때

	
protected:
	vector<Dragon> dragonCount[(UINT)Team::END];

	UI* dragonSoulUI = nullptr;
	UI* dragonCountUI[(UINT)Team::END][4] = { nullptr, };
	
	vector<Champion*> championInfo[(UINT)Team::END];
	vector<UI*> championScoreUI[(UINT)Team::END];
	
	Label* turretCountLabel[(UINT)Team::END] = { nullptr, };
	Label* killCountLabel[(UINT)Team::END] = { nullptr, };

	Dragon dragonSoul;

	
};

