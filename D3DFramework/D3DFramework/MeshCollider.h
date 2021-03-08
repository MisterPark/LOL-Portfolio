#pragma once
#include "Collider.h"

namespace Engine
{
	class MeshCollider : public Collider
	{
    public:
        explicit MeshCollider(GameObject* owner);
        explicit MeshCollider(const MeshCollider& rhs);
        virtual ~MeshCollider();

        virtual void Render() override;
        virtual IComponent* Clone() override;
        virtual bool Raycast(Ray ray, RaycastHit* outHitInfo, float maxDistance) override;

        void SetSharedMesh();
        Mesh* GetSharedMesh();

    public:
        Mesh* sharedMesh = nullptr;
	};

}

