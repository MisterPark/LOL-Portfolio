#pragma once
#include "Collider.h"

namespace PKH
{
	class MeshCollider : public Collider
	{
    public:
        explicit MeshCollider(GameObject* owner);
        explicit MeshCollider(const MeshCollider& rhs);
        virtual ~MeshCollider();

        virtual IComponent* Clone() override;
        virtual bool Raycast(Ray ray, RaycastHit* outHitInfo, float maxDistance) override;



    public:
        Mesh* sharedMesh = nullptr;
	};

}

