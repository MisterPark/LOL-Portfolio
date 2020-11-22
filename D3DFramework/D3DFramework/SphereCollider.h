#pragma once
#include "Collider.h"
class SphereCollider :
    public Collider
{
public:
    explicit SphereCollider(GameObject* owner);
    explicit SphereCollider(const SphereCollider& rhs);
    virtual ~SphereCollider();

    virtual IComponent* Clone() override;
    virtual void OnCollisionEnter(const Collider* other) override;
    virtual bool Raycast(Ray ray, RaycastHit hitInfo, float maxDistance) override;

public:
    // ±¸ ¹Ý°æ
    float radius;

    
};

