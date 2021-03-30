#pragma once
#include "Scene.h"

class Label;
class Champion;
class Unit;
class PlayerInfoPanel;

class GameScene :
    public Scene
{
public:
    GameScene();
    // Scene을(를) 통해 상속됨
    virtual void OnLoaded() override;
    virtual void OnUnloaded() override;
    virtual void Update() override;

    void PacketProc(CPacket* pPacket);
    void NetProc();

    void ReqTime();
    void ResTime(CPacket* pack);
    void ResMove(CPacket* pack);
    void ResAttack(CPacket* pack);
    void ResDamage(CPacket* pack);

    void ReqCreateMinionCaster();
    void ResCreateMinionCaster(CPacket* pack);

    void CreateEnvironment();
    void CreateChampion();
    void CreateBuilding();
    void CreateMonster();

    void CreateMinionCaster();
    void CreateMinionMelee();
    void CreateMinionSiege();
    void CreateMinionSuper();
    

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

