#include "stdafx.h"
#include "BoxCollider.h"

using namespace PKH;

BoxCollider::BoxCollider(GameObject* owner)
    :Collider(owner)
{
    type = ColliderType::Box;
    LPD3DXMESH mesh;
    size = { 1,1,1 };
    auto device = RenderManager::GetDevice();
    //RenderManager::LockDevice();
    D3DXCreateBox(device, size.x, size.y, size.z, &mesh, nullptr);
    
    
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
    
    SetMeshInformation();
}

BoxCollider::BoxCollider(const BoxCollider& rhs)
    :Collider(rhs)
{
    
}

BoxCollider::~BoxCollider()
{
}

IComponent* BoxCollider::Clone()
{
    return new BoxCollider(*this);
}

bool BoxCollider::Raycast(Ray ray, RaycastHit* outHitInfo, float maxDistance)
{
    // TODO : (약함)로컬에서 충돌검사를 해야 빠르겠지...?
    Matrix matWorld = Matrix::identity;
    matWorld._41 = transform->position.x;
    matWorld._42 = transform->position.y;
    matWorld._43 = transform->position.z;
    
    float u, v, dist;
    DWORD index;
    for (UINT i = 0; i < triangleCount; i++)
    {
        index = i * 3;
        Vector3 v1 = vertexPositions[indices[index]];
        Vector3 v2 = vertexPositions[indices[index + 1]];
        Vector3 v3 = vertexPositions[indices[index + 2]];

        D3DXVec3TransformCoord(&v1, &v1, &matWorld);
        D3DXVec3TransformCoord(&v2, &v2, &matWorld);
        D3DXVec3TransformCoord(&v3, &v3, &matWorld);
        

        if (D3DXIntersectTri(&v1,&v2, &v3,
            &ray.origin, &ray.direction, &u, &v, &dist))
        {
            if (outHitInfo != nullptr)
            {
                // V1 + U(V2 - V1) + V(V3 - V1)
                outHitInfo->point = v1 + u * (v2 - v1) + v * (v3 - v1);
                outHitInfo->distance = dist;
                outHitInfo->collider = this;
            }

            return true;
        }
    }


    return false;
}