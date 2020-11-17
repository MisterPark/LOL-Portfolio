#pragma once
#include "CustomMesh.h"

namespace PKH
{
    class Rectangle :
        public CustomMesh
    {
    public:
        Rectangle();
        virtual ~Rectangle();

        // CustomMesh을(를) 통해 상속됨

        virtual void Update() override;

        virtual IComponent* Clone() override;
    };
}
