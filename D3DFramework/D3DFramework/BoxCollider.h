#pragma once
#include "Collider.h"
class BoxCollider :
    public Collider
{
public:
    explicit BoxCollider(GameObject* owner);
    explicit BoxCollider(const BoxCollider& rhs);
    virtual ~BoxCollider();

    virtual IComponent* Clone() override;
    virtual void OnCollisionEnter(const Collider* other) override;
    virtual bool Raycast(Ray ray, RaycastHit hitInfo, float maxDistance) override;

public:
    // 각축의 길이
    Vector3 size;
};

