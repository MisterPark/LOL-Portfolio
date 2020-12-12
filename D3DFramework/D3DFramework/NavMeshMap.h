#pragma once
#include "GameObject.h"

namespace PKH
{
    class NavMeshMap :
        public GameObject
    {
    public:
        NavMeshMap();
        virtual ~NavMeshMap();

        // GameObject을(를) 통해 상속됨
        virtual void Initialize() override;
        virtual void Release() override;
        virtual void Update() override;

    private:
        void SetNavigationInfo();
    public:
        bool Search(const Vector3& start, const Vector3& dest);
        PathFinder::Node* GetResultNode();

    private:
        NavMesh* navMesh = nullptr;
        PathFinder* pPathFinder = nullptr;
    };
}


