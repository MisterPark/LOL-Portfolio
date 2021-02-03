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

    Red1,
    Red2,
    Blue1,
    Blue2,
    Murkwolf1,
    Murkwolf_Mini1,
    Murkwolf_Mini2,
    Murkwolf2,
    Murkwolf_Mini3,
    Murkwolf_Mini4,
    Gromp1,
    Gromp2,
    Razorbeak1,
    Razorbeak_Mini1,
    Razorbeak_Mini2,
    Razorbeak_Mini3,
    Razorbeak_Mini4,
    Razorbeak_Mini5,
    Razorbeak2,
    Razorbeak_Mini6,
    Razorbeak_Mini7,
    Razorbeak_Mini8,
    Razorbeak_Mini9,
    Razorbeak_Mini10,
    Krug1,
    Krug2,
    Scuttleracer1,
    Scuttleracer2,
    END
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

