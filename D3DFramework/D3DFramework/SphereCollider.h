#pragma once
#include "Collider.h"

namespace PKH
{
    class SphereCollider :
        public Collider
    {
    public:
        explicit SphereCollider(GameObject* owner);
        explicit SphereCollider(const SphereCollider& rhs);
        virtual ~SphereCollider();

        virtual IComponent* Clone() override;
        virtual bool Raycast(Ray ray, RaycastHit* outHitInfo, float maxDistance) override;

    public:
        // ±¸ ¹Ý°æ
        float radius;


    };


}
