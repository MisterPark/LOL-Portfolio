#pragma once
#include "Panel.h"
#include "Unit.h"

class Champion;

enum class Dragon
{
	Wind,	// 바람
	Fire,	// 화염
	Earth,	// 대지
	Water,	// 바다
	Break,	// X
	Elder,	// 장로
	End
};

enum class MobTimeID
{
	SouthRed, // 블루팀 레드 (남)
	NorthRed, // 레드팀 레드 (북)
	WestBlue, // 블루팀 블루 (서)
	EastBlue, // 레드팀 블루 (동)
	Dragon,	  // 용
	Baron,	  // 바론
	Herald,	  // 협곡의 전령
	End
};

enum class PublicScoreID
{
	RedTeamKillScore,
	BlueTeamKillScore,
	RedTeamTurretKillScore,
	BlueTeamTurretKillScore,
	END
};

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
	
	void SetMobTime(MobTimeID _mob, float _time);
	void SetDragonTime(float _time, Dragon _dragon);
	void AddPublicScore(PublicScoreID _id) { publicScore[(int)_id]++; }
	int GetPublicScore(PublicScoreID _id) { return publicScore[(int)_id]; }

	virtual void Show();
	virtual void Hide();
	
protected:
	vector<Dragon> dragonCount[(UINT)Team::END];

	UI* dragonSoulUI = nullptr;
	UI* dragonCountUI[(UINT)Team::END][4] = { nullptr, };
	
	vector<Champion*> championInfo[(UINT)Team::END];
	vector<UI*> championScoreUI[(UINT)Team::END];
	UI* championItemUI[(UINT)Team::END][5][7];

	Label* turretCountLabel[(UINT)Team::END] = { nullptr, };
	Label* killCountLabel[(UINT)Team::END] = { nullptr, };

	Dragon dragonSoul;

	// 용시간
	Label* timeLabel[(UINT)MobTimeID::End] = { nullptr, };
	UI* simbolBig[(UINT)MobTimeID::End] = { nullptr, };
	UI* simbolSmall[(UINT)MobTimeID::End] = { nullptr, };
	float mobTime[(UINT)MobTimeID::End] = { 0.f, };

	int publicScore[(UINT)PublicScoreID::END] = { 0, };
};

