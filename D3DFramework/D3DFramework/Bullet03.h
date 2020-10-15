#pragma once
#include "GameObject.h"


namespace PKH
{
    class Bullet03 :
        public GameObject
    {
    public:
        Bullet03();
       
        virtual ~Bullet03();
        // GameObject을(를) 통해 상속됨
        virtual void Update() override;
        Vector3 TargetPos;
        bool MyBullet03 = false;
        bool isBossBullet = false;
        int BossBullet1 = 0;
        int Extinction = 0;
        float DieTime = 0.f;
        bool isSetting = false;
    };
}
