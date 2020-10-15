#pragma once
#include "GameObject.h"

namespace PKH
{
    class MonsterBullet4 :
        public GameObject
    {
    public:
        // GameObject을(를) 통해 상속됨
        MonsterBullet4();
        ~MonsterBullet4();
        virtual void Update() override;
        void OnCollision(GameObject* target);
        void Ready();
        
    public:
        int GetPosZ() { return BulletPosZ; }
        void SetCode(int CodeSet) { BulletCode = CodeSet; }
        void SetDir(Vector3 _Dir) { dir = _Dir; }
        void SetPosZ(int PosZ) { BulletPosZ = PosZ; }
    public:
        GameObject* TargetPlayer;
        Vector3 TargetPos;
        int BulletCode;
        int BulletPosZ;
        Vector3 dir;
    };
}

