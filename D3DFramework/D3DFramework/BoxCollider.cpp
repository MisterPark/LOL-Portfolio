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
    RenderManager::LockDevice();
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
    // TODO : 여기서부터 시작
    // 수정해야함 
    Matrix matWorld = GetWorldMatrix();
    Matrix::Inverse(matWorld);

    Ray localRay = ray;
    D3DXVec3TransformCoord(&localRay.origin, &ray.origin, &matWorld);
    D3DXVec3TransformNormal(&localRay.direction, &ray.direction, &matWorld);
    Vector3::Normalize(&localRay.direction);

    float u, v, dist;
    WORD index;
    for (int i = 0; i < faceCount; i++)
    {
        // V1 + U(V2 - V1) + V(V3 - V1)
        index = indices[i * 3];
        if (D3DXIntersectTri(&vertexPositions[index],
            &vertexPositions[index + 1], &vertexPositions[index + 2],
            &localRay.origin, &localRay.direction, &u, &v, &dist))
        {
            if (outHitInfo != nullptr)
            {
                Vector3 v1 = vertexPositions[index];
                Vector3 v2 = vertexPositions[index+1];
                Vector3 v3 = vertexPositions[index+2];

                outHitInfo->point.x = v1.x + u * (v2.x - v1.x) + v * (v3.x - v1.x);
                outHitInfo->point.y = v1.y + u * (v2.y - v1.y) + v * (v3.y - v1.y);
                outHitInfo->point.z = v1.z + u * (v2.z - v1.z) + v * (v3.z - v1.z);

                outHitInfo->distance = dist;

                outHitInfo->collider = this;
            }

            return true;
        }
    }


    return false;
}