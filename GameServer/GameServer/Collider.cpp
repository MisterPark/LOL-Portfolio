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
	
	Safe_Release(&pMesh);
	Safe_Delete_Array(&vertexPositions);
	Safe_Delete_Array(&indices);
	vertexPositions = nullptr;
	indices = nullptr;
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
	//return;
	auto device = RenderManager::GetDevice();
	RenderManager::LockDevice();
	
	
	device->SetTransform(D3DTS_WORLD, &world);

	LPDIRECT3DVERTEXBUFFER9 vb;
	pMesh->GetVertexBuffer(&vb);
	LPDIRECT3DINDEXBUFFER9 ib;
	pMesh->GetIndexBuffer(&ib);

	//device->SetStreamSource(0, vb, 0, pMesh->GetNumVertices());
	//device->SetFVF(fvf);
	//device->SetIndices(ib);

	device->SetRenderState(D3DRS_LIGHTING, false);
	device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	
	device->SetTexture(0,0);
	pMesh->DrawSubset(0);
	//device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, pMesh->GetNumVertices(), 0, pMesh->GetNumFaces());


	device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	device->SetRenderState(D3DRS_LIGHTING, false);
	//device->SetFVF(originFVF);
	RenderManager::UnlockDevice();

	// TODO : 반드시 지워야함 DEBUG코드
	//SetColor(D3DCOLOR_ARGB(255, 0, 255, 0));
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

Matrix PKH::Collider::GetWorldMatrix()
{
	if (transform == nullptr)return Matrix::identity;

	return transform->world;
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

void PKH::Collider::SetLayer(Layer layer)
{
	CollisionManager::GetInstance()->DisregisterObject(this);
	CollisionManager::RegisterObject(layer, this);
}

void PKH::Collider::SetMeshInformation()
{
	if (pMesh == nullptr)return;
	void* pVertex = nullptr;
	pMesh->LockVertexBuffer(0, &pVertex);
	// 버텍스 위치 정보 찾기
	D3DVERTEXELEMENT9 decl[MAX_FVF_DECL_SIZE];
	ZeroMemory(decl, sizeof(D3DVERTEXELEMENT9) * MAX_FVF_DECL_SIZE);

	pMesh->GetDeclaration(decl);

	BYTE offset = 0;
	for (int i = 0; i < MAX_FVF_DECL_SIZE; i++)
	{
		if (decl[i].Usage == D3DDECLUSAGE_POSITION)
		{
			offset = (BYTE)decl[i].Offset;
			break;
		}
	}
	// 버텍스 카운트 세팅
	vertexCount = pMesh->GetNumVertices();
	// 버텍스 포지션 배열 생성
	vertexPositions = new Vector3[vertexCount];

	int vertexSize = D3DXGetFVFVertexSize(fvf);
	for (int i = 0; i < vertexCount; ++i)
	{
		Vector3* pos = ((Vector3*)(((BYTE*)pVertex) + (i * vertexSize + offset)));
		vertexPositions[i] = *pos;
	}

	pMesh->UnlockVertexBuffer();

	

	//==================================
	// TODO : 인덱스버퍼 크기 찾는 코드
	


	// 삼각형 갯수 세팅
	triangleCount = pMesh->GetNumFaces();
	int indexCount = triangleCount * 3;
	indices = new DWORD[indexCount];

	// 인덱스 버퍼 세팅
	LPDIRECT3DINDEXBUFFER9 pIB;
	pMesh->GetIndexBuffer(&pIB);

	D3DINDEXBUFFER_DESC desc;
	pIB->GetDesc(&desc);
	D3DFORMAT format = desc.Format;
	UINT indexSize = 2; // INDEX16
	if (format == D3DFORMAT::D3DFMT_INDEX16)
	{
		WORD* dummyIndices = nullptr;
		pMesh->LockIndexBuffer(0, (void**)&dummyIndices);
		for (int i = 0; i < indexCount; i++)
		{
			WORD idx = dummyIndices[i];
			indices[i] = idx;
		}
		pMesh->UnlockIndexBuffer();
	}
	else
	{
		DWORD* dummyIndices = nullptr;
		pMesh->LockIndexBuffer(0, (void**)&dummyIndices);
		for (int i = 0; i < indexCount; i++)
		{
			DWORD idx = dummyIndices[i];
			indices[i] = idx;
		}
		pMesh->UnlockIndexBuffer();
	}

	


}
