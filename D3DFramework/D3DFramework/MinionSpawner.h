#pragma once
#include "Minion.h"

enum class SpawnLane { BlueTop, BlueMid, BlueBot, RedTop, RedMid, RedBot, END};
enum class PhaseType { MMMCCC, MMMSCCC, SMMMCCC, SSMMMCCC, END };

class MinionSpawner
{
private:
	MinionSpawner();
	~MinionSpawner();

public:
	static MinionSpawner* GetInstance();
	static void Destroy();

    static void Update();

    static void Spawn();

    Minion* CreateMinion(MinionType _type, Team _team, SpawnLane _spawnLane);

    static void SetMinionPhase(SpawnLane _spawnLane, PhaseType _phaseType);

private:
    // 해당 레인의 미니언 페이즈는 몇인지
    PhaseType spawnPhase[MaxOfEnum<SpawnLane>()] = {};
    // 페이즈별 생성 타입,순서
    vector<MinionType> phase[MaxOfEnum<PhaseType>()];
    // 해당 레인의 생성할 미니언은 몇번째 미니언인지
    int spawnCount = 0;
    // 해당 레인의 스폰 위치
    Vector3 spawnPosition[MaxOfEnum<SpawnLane>()] = {};
    // 해당 레인의 웨이포인트
    vector<Vector3> wayPoints[MaxOfEnum<SpawnLane>()] = {};

    bool spawnFlag = false;
    float spawnTick = 0.f;
    float spawnDelay = 0.5f;

};

