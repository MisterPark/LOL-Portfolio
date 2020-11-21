#pragma once
#include "IComponent.h"

namespace PKH
{
    class Collider :
        public IComponent
    {
    public:
        // IComponent을(를) 통해 상속됨
        virtual IComponent* Clone() = 0;
        virtual void OnCollisionEnter(const Collider* other) = 0;
    };

}

