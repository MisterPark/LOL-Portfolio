#include "stdafx.h"
#include "Trail.h"
#include "DynamicMesh.h"
#include "Effect_Trail.h"

using namespace Engine;

Trail::Trail(GameObject* owner)
	:IComponent(owner)
{
	trail = (Effect_Trail*)SceneManager::GetCurrentScene()->CreateObject<Effect_Trail>(Layer::Effect);
	trail->SetDuration(INFINITY);
	trail->Hide();

	DynamicMesh* dmesh = (DynamicMesh*)owner->GetComponent<DynamicMesh>();
	if (dmesh == nullptr) return;
	auto weaponFrame = dmesh->GetFrameByName("Weapon");
	if (weaponFrame == nullptr) return;

	this->dynamicMesh = dmesh;

}

Trail::Trail(const Trail& rhs)
	:IComponent(rhs)
{
}

Trail::~Trail()
{
	dynamicMesh = nullptr;
	if (trail)
	{
		trail->Destroy();
		trail = nullptr;
	}
}

void Trail::Update()
{
	if (dynamicMesh == nullptr) return;
	auto worldMatrix = transform->GetWorldMatrix();
	auto weaponFrame = dynamicMesh->GetFrameByName("Weapon");
	Matrix weaponMatrix = weaponFrame->CombinedTransformationMatrix * worldMatrix;
	Vector3 weaponPos;
	D3DXVec3TransformCoord(&weaponPos, &weaponPos, &weaponMatrix);
	Vector3 weaponDirection = (Vector3)(*(Vector3*)&weaponMatrix._31);
	weaponDirection = weaponDirection.Normalized();
	weaponPos += (weaponDirection * this->offset);
	Vector3 weaponTip = weaponPos + (weaponDirection * this->length);
	if (trail != nullptr)
	{
		trail->SetTrailPos(weaponPos, weaponTip);
	}
}

IComponent* Trail::Clone()
{
	return nullptr;
}

void Trail::AttachToDynamicMesh(DynamicMesh* dmesh)
{
	this->dynamicMesh = dmesh;
}

void Trail::SetLength(float _length)
{
	this->length = _length;
}

void Trail::SetOffset(float _offset)
{
	this->offset = _offset;
}

void Trail::SetVisible(bool _visible)
{
	visible = _visible;
	if (trail)
	{
		trail->Show(_visible);
	}
}
