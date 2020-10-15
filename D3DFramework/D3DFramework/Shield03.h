#pragma once
#include "GameObject.h"


namespace PKH
{
    class Shield03 :
        public GameObject
    {
    public:
        Shield03();

        virtual ~Shield03();
        // GameObject을(를) 통해 상속됨
        virtual void Update() override;

        float tick = 0.f;
        float DieTime = 0.f;
        float delay = 1.f;

        bool isSetting = false;
    };
}
