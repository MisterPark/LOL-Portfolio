#pragma once
#include "GameObject.h"
#include "Stat.h"
#include "DamageCalc.h"

class DamageObject : public GameObject
{
public:
    DamageObject();
    virtual ~DamageObject();

    virtual void Initialize() override;
    virtual void Release() override;
    virtual void Update() override;

    virtual void OnCollisionEnter(Collider* target);

    //_pos : 위치
    //_scale : 크기(float)
    //_team : 팀
    //_attack : 공격력
    // _lifeTime = 살아있을시간
    // _interval = 새롭게 때리는 주기/시간  // Default = 한번만 때림
    // _interval_Attack = 새롭게 때리고 데미지판정 시간 // Default = 새롭게 때릴때까지 쭉 판정
    // _startTime = 생성하고 언제부터 때릴건지. // Default = 0.f 바로
    void Set_DamageObject(Unit* _hostObject, Vector3 _pos, float _scale, Team _team, float _attack, float _lifeTime, float _interval = 0.f, float _interval_AttackTime = -1.f, float _startTime = 0.f);
    void Set_ObjectFollow(Unit* _object);
    Unit* Get_pHostObject() { return hostObject; }
    bool Check_DamagedOverlap(GameObject* damagedObject);
    void Add_DamageCalc(DamageCalc* _damageCalc);

private:
    void ObjectFollowMove();
    void Calc_StartOfInterval();
    void Calc_FinalDamage(float* _damage, Stat* _myStat, Stat* _targetStat);

private:
    Team team = Team::NEUTRAL;
    float attackDamage = 0.f;
    float lifeTime = 0.f;                   //살아있는시간
    float interval_Init = 0.f;              //때리는주기초기화
    float interval_Time = 0.f;              //때리는주기실시간
    float interval_Attack_Init = 0.f;       //때리고나서판정시간초기화
    float interval_Attack_Time = 0.f;       //때리고나서판정실시간
    float startTime = 0.f;
    bool attackCheck = false;

    Unit* hostObject = nullptr;
    Unit* followObject = nullptr;
    list<DamageCalc*> damageCalcList;   //데미지계산관련
public:
    list<GameObject*> damagedObject;
    //list<CC기*> 이 데미지 오브젝트 가질 CC기들
};
