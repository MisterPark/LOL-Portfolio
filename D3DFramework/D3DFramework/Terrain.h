#pragma once
#include "CustomMesh.h"

namespace Engine
{
    class Terrain :
        public CustomMesh
    {
    public:
        explicit Terrain(GameObject* owner);
        explicit Terrain(const Terrain& rhs);
        virtual ~Terrain();

        virtual void CreateCustomMesh() override;


        virtual void Update() override;

        virtual IComponent* Clone() override;

        void LoadHeightMap(const string& filePath);
        bool GetYFromPoint(float* _outY, float _x, float _z);


    private:
        // ¹ý¼±º¤ÅÍ
        void SetNormalVector();

    private:
        int width = dfTERRAIN_WIDTH;
        int height = dfTERRAIN_WIDTH;

        Vector3* vertexInfo = nullptr;

       
    };


}
