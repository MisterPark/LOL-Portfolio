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
        bool GetYFromPoint(float* _outY, float _x, float _z);


    private:
        // 법선벡터
        void SetNormalVector();

    private:
        int width = dfTERRAIN_WIDTH;
        int height = dfTERRAIN_WIDTH;

        Vector3* vertexInfo = nullptr;
    };


}
