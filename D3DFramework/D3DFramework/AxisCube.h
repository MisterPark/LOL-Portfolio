#pragma once
#include "Mesh.h"


namespace PKH
{
    class AxisCube :
        public Mesh
    {
    public:
        AxisCube();
        virtual ~AxisCube();

        // Mesh을(를) 통해 상속됨

        virtual void Update() override;
        virtual void Render(Vector3 _pos, Vector3 _aixs);
        

        virtual IComponent* Clone() override;
    };

}