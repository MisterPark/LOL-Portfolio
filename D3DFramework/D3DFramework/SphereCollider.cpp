#include "stdafx.h"
#include "SphereCollider.h"

using namespace PKH;

SphereCollider::SphereCollider(GameObject* owner)
    :Collider(owner)
{
    type = ColliderType::Sphere;
    LPD3DXMESH mesh;
    radius = 0.5f;
    auto device = RenderManager::GetDevice();
    RenderManager::LockDevice();
    D3DXCreateSphere(device, radius, 16, 16, &mesh, nullptr);

    fvf = mesh->GetFVF();
    if (!(fvf & D3DFVF_DIFFUSE))
    {
        mesh->CloneMeshFVF(mesh->GetOptions(), fvf |= D3DFVF_DIFFUSE, device, &pMesh);
    }
    else
    {
        mesh->CloneMeshFVF(mesh->GetOptions(), fvf, device, &pMesh);
    }

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
        *pColor = D3DCOLOR_ARGB(255, 0, 255, 0);
    }

    pMesh->UnlockVertexBuffer();

    RenderManager::UnlockDevice();
}

SphereCollider::SphereCollider(const SphereCollider& rhs)
    :Collider(rhs)
{
}

SphereCollider::~SphereCollider()
{
}

IComponent* SphereCollider::Clone()
{
    return new SphereCollider(*this);
}

bool SphereCollider::Raycast(Ray ray, RaycastHit* outHitInfo, float maxDistance)
{
    return false;
}
