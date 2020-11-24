#include "stdafx.h"
#include "Physics.h"
#include "Collider.h"

bool PKH::Physics::Raycast(Ray ray, RaycastHit* outHit, float maxDistance, int layerMask)
{
    auto colliderTable = CollisionManager::GetInstance()->objectList;
    int beginLayer = (int)Layer::Default;
    int endLayer = (int)Layer::END;
    for (int i = beginLayer; i < endLayer; i++)
    {
        Layer layer = (Layer)i;
        int mask = LayerMask::GetMask(layer);
        if ((mask & layerMask) == false) continue;
        
        auto colliderList = colliderTable[i];
        for (Collider* collider : colliderList)
        {
            if (collider->Raycast(ray, outHit, maxDistance))
            {
                return true;
            }
        }
    }
    return false;
}

bool PKH::Physics::Raycast(Vector3 origin, Vector3 direction, float maxDistance, int layerMask)
{
    Ray ray;
    ray.origin = origin;
    ray.direction = direction;

    auto colliderTable = CollisionManager::GetInstance()->objectList;
    int beginLayer = (int)Layer::Default;
    int endLayer = (int)Layer::END;
    for (int i = beginLayer; i < endLayer; i++)
    {
        Layer layer = (Layer)i;
        int mask = LayerMask::GetMask(layer);
        if ((mask & layerMask) == false) continue;

        auto colliderList = colliderTable[i];
        for (Collider* collider : colliderList)
        {
            if (collider->Raycast(ray, nullptr, maxDistance))
            {
                return true;
            }
        }
    }
    return false;
}
