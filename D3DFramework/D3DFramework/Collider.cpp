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

void PKH::Collider::Update()
{
	if (gameObject == nullptr)return;
	if (transform == nullptr)return;

	world = Matrix::identity;

	world._41 = center.x + transform->position.x;
	world._42 = center.y + transform->position.y;
	world._43 = center.z + transform->position.z;
}

void PKH::Collider::Render()
{
	if (pMesh == nullptr)return;
	if (gameObject == nullptr)return;
	if (transform == nullptr)return;

	auto device = RenderManager::GetDevice();
	RenderManager::LockDevice();
	
	device->SetTransform(D3DTS_WORLD, &world);
	device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	
	pMesh->DrawSubset(0);

	device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	RenderManager::UnlockDevice();

	// TODO : 반드시 지워야함 DEBUG코드
	SetColor(D3DCOLOR_ARGB(255, 0, 255, 0));
}

void PKH::Collider::OnCollisionEnter(const Collider* other)
{
	if (gameObject == nullptr) return;

	gameObject->OnCollisionEnter(other);
}

Vector3 PKH::Collider::GetWorldPosition()
{
	if (transform == nullptr) return Vector3(0, 0, 0);
	Vector3 worldPos = transform->position + center;
	return worldPos;
}

void PKH::Collider::SetColor(D3DCOLOR color)
{
	if (pMesh == nullptr)return;
	void* pVertex = nullptr;
	pMesh->LockVertexBuffer(0, &pVertex);
	// 색상 정보 위치 찾기 (초록색으로 바꾸려고)
	D3DVERTEXELEMENT9 decl[MAX_FVF_DECL_SIZE];
	ZeroMemory(decl, sizeof(D3DVERTEXELEMENT9) * MAX_FVF_DECL_SIZE);

	pMesh->GetDeclaration(decl);

	BYTE offset = 0;
	for (int i = 0; i < MAX_FVF_DECL_SIZE; i++)
	{
		if (decl[i].Usage == D3DDECLUSAGE_COLOR)
		{
			offset = (BYTE)decl[i].Offset;
			break;
		}
	}
	int vertexCount = pMesh->GetNumVertices();
	int vertexSize = D3DXGetFVFVertexSize(fvf);
	for (int i = 0; i < vertexCount; ++i)
	{
		DWORD* pColor = ((DWORD*)(((BYTE*)pVertex) + (i * vertexSize + offset)));
		*pColor = color;
	}

	pMesh->UnlockVertexBuffer();
}
