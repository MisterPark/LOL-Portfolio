#pragma once
#include "Mesh.h"

namespace PKH
{
    class Cube :
        public Mesh
    {
    public:
        Cube();
        virtual ~Cube();

        // Mesh을(를) 통해 상속됨

        virtual void Update() override;

        virtual IComponent* Clone() override;
    };
}
