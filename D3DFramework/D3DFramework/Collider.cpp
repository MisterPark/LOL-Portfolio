#include "stdafx.h"
#include "Collider.h"


PKH::Collider::Collider(GameObject* owner)
	:IComponent(owner)
{
	if (owner == nullptr)return;
	CollisionManager::RegisterObject(owner->GetLayer(), this);
}

PKH::Collider::Collider(const Collider& rhs)
	: IComponent(rhs)
{
	
}

PKH::Collider::~Collider()
{
	
	if (gameObject != nullptr)
	{
		CollisionManager::DisregisterObject(gameObject->GetLayer(), this);
	}
	
	Safe_Release(pMesh);
}

void PKH::Collider::Render()
{
	if (pMesh == nullptr)return;
	if (gameObject == nullptr)return;
	if (transform == nullptr)return;

	// 월드 계산
	Matrix world = transform->world;
	world._41 += center.x;
	world._42 += center.y;
	world._43 += center.z;

	auto device = RenderManager::GetDevice();
	RenderManager::LockDevice();
	
	device->SetTransform(D3DTS_WORLD, &world);
	device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	
	pMesh->DrawSubset(0);

	device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	RenderManager::UnlockDevice();
}
