#pragma once
#include "CustomMesh.h"

namespace Engine
{
    class Triangle : public CustomMesh
    {
    public:
        explicit Triangle(GameObject* owner);
        explicit Triangle(const Triangle& rhs);
        virtual ~Triangle();

        virtual void CreateCustomMesh() override;

        virtual void Update() override;

		virtual IComponent* Clone() override;

        
    };


}