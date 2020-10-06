#pragma once
#include "Mesh.h"

namespace PKH
{
    class Triangle :
        public Mesh
    {
    public:
        Triangle();
        virtual ~Triangle();

        // Mesh을(를) 통해 상속됨

        virtual void Update() override;
		virtual void Render() override;

		virtual IComponent* Clone() override;
    };


}