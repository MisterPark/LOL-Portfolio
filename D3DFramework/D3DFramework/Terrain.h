#pragma once
#include "Mesh.h"

namespace PKH
{
    class Terrain :
        public Mesh
    {
    public:
        Terrain();
        virtual ~Terrain();

        // Mesh을(를) 통해 상속됨

        virtual void Update() override;

        virtual IComponent* Clone() override;

        void LoadHeightMap(const string& filePath);

        int width = 129;
        int height = 129;
    };


}
