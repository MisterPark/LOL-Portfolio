#pragma once
#include "CustomMesh.h"

namespace PKH
{
    class Rectangle : public CustomMesh
    {
    public:
        explicit Rectangle(GameObject* owner);
        explicit Rectangle(const Rectangle& rhs);
        virtual ~Rectangle();

        // CustomMesh을(를) 통해 상속됨

        virtual void Update() override;

        virtual IComponent* Clone() override;

        // CustomMesh을(를) 통해 상속됨
        virtual void CreateCustomMesh() override;
    };
}
