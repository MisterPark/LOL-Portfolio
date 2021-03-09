#pragma once
#include "Panel.h"
#include "Unit.h"

class Champion;

enum class Drake
{
	CLOUD,		// 바람
	INFERNAL,	// 화염
	MOUNTAIN,	// 대지
	OCEAN,		// 바다
	BREAK,		// X
	END
};

extern std::wstring drakeCountTex[(UINT)Drake::END];
extern std::wstring drakeSoulTex1[(UINT)Drake::END];
extern std::wstring drakeSoulTex2[(UINT)Drake::END];

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
	void AddDrake(Drake _drake, Team _team);
	void SetDrakeSoul(Drake _drake); // 3용 이후 용 결정될 때
	void SetDrakeSoulBuf(); // 4용 버프 적용될 때

	
protected:
	vector<Drake> DrakeCount[(UINT)Team::END];

	UI* DrakeSoulUI = nullptr;
	UI* DrakeCountUI[(UINT)Team::END][4] = { nullptr, };
	
	vector<Champion*> ChampionInfo[(UINT)Team::END];
	vector<UI*> ChampionScoreUI[(UINT)Team::END];
	
	Label* TurretCountLabel[(UINT)Team::END] = { nullptr, };
	Label* KillCountLabel[(UINT)Team::END] = { nullptr, };

	Drake DrakeSoul;

	
};

