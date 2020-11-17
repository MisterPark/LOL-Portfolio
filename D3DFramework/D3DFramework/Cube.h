#pragma once
#include "CustomMesh.h"

namespace PKH
{
    class Cube :
        public CustomMesh
    {
    public:
        Cube();
        virtual ~Cube();

        // CustomMesh을(를) 통해 상속됨

        virtual void Update() override;
        
        virtual IComponent* Clone() override;

    };
}
 