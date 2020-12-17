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
        // 메시의 폴리곤으로 노드를 생성(old version)
        void SetNavigationInfo();
        // 저장된 데이터로 노드를 생성(new version)
        void LoadNavigationInfo();
    public:
        bool Search(const Vector3& start, const Vector3& dest);
        PathFinder::Node* GetResultNode();

    private:
        NavMesh* navMesh = nullptr;
        PathFinder* pPathFinder = nullptr;
    };
}


