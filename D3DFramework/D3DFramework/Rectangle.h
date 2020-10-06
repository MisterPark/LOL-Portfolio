#pragma once
#include "Mesh.h"

namespace PKH
{
    class Rectangle :
        public Mesh
    {
    public:
        Rectangle();
        virtual ~Rectangle();

        // Mesh을(를) 통해 상속됨

        virtual void Update() override;
        virtual void Render() override;

        virtual IComponent* Clone() override;
    };
}
