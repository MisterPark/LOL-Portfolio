#pragma once
#include "IScene.h"

class Label;
class Champion;
class Unit;
class PlayerInfoPanel;

enum class UnitID
{
    Champ0,Champ1,Champ2,Champ3,Champ4,Champ5,Champ6,Champ7,Champ8,Champ9,
    TurretBlueBot1,
    TurretBlueBot2,
    TurretBlueBot3,
    TurretBlueMid1,
    TurretBlueMid2,
    TurretBlueMid3,
    TurretBlueTop1,
    TurretBlueTop2,
    TurretBlueTop3,
    TurretBlueTwin1,
    TurretBlueTwin2,

    TurretRedBot1,
    TurretRedBot2,
    TurretRedBot3,
    TurretRedMid1,
    TurretRedMid2,
    TurretRedMid3,
    TurretRedTop1,
    TurretRedTop2,
    TurretRedTop3,
    TurretRedTwin1,
    TurretRedTwin2,
};

class GameScene :
    public IScene
{
public:
    GameScene();
    // IScene을(를) 통해 상속됨
    virtual void OnLoaded() override;
    virtual void OnUnloaded() override;
    virtual void Update() override;

    void PacketProc(CPacket* pPacket);
    void NetProc();

    void ReqTime();
    void ResTime(CPacket* pack);
    void ResMove(CPacket* pack);
    void ResAttack(CPacket* pack);

    void CreateEnvironment();
    void CreateChampion();
    void CreateBuilding();

    Network* net = nullptr;
    Vector3 spawnPos[10];

    PlayerInfoPanel* playerInfo;

    map<INT,Unit*> unitMap;
    // 시간측정
    DWORD oldTime = 0;
    float sendTick = 0.f;
    float sendDelay = 1.f;
    Label* latencyLabel = nullptr;
};

