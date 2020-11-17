#pragma once
#include "CustomMesh.h"

namespace PKH
{
    class Triangle :
        public CustomMesh
    {
    public:
        Triangle();
        virtual ~Triangle();

        // CustomMesh을(를) 통해 상속됨

        virtual void Update() override;

		virtual IComponent* Clone() override;
    };


}