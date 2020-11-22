#pragma once
#include "CustomMesh.h"

namespace PKH
{
    class Cube :
        public CustomMesh
    {
    public:
        explicit Cube(GameObject* owner);
        explicit Cube(const Cube& rhs);
        virtual ~Cube();

        virtual void CreateCustomMesh() override;

        virtual void Update() override;
        
        virtual IComponent* Clone() override;


       

    };
}
 