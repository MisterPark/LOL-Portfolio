#pragma once
#include "CustomMesh.h"

namespace Engine
{
    class Rectangle : public CustomMesh
    {
    public:
        explicit Rectangle(GameObject* owner);
        explicit Rectangle(const Rectangle& rhs);
        virtual ~Rectangle();

        virtual void Update() override;
        virtual IComponent* Clone() override;
        virtual void CreateCustomMesh() override;
    };
}
