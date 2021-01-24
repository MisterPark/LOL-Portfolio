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


        virtual void Render();
        virtual IComponent* Clone() override;
        virtual bool Raycast(Ray ray, RaycastHit* outHitInfo, float maxDistance) override;

        void SetRadius(float _radius);
        float GetRadius();
    
    protected:
        // ±¸ ¹Ý°æ
        float radius;


    };


}
