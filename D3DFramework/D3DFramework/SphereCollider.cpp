#include "stdafx.h"
#include "SphereCollider.h"

using namespace Engine;

Engine::SphereCollider::SphereCollider(GameObject* owner)
    :Collider(owner)
{
    type = ColliderType::Sphere;
    LPD3DXMESH mesh;
    radius = 1.f;
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

    SetMeshInformation();
}

Engine::SphereCollider::SphereCollider(const SphereCollider& rhs)
    :Collider(rhs)
{
}

Engine::SphereCollider::~SphereCollider()
{
}

void Engine::SphereCollider::Render()
{
    if (pMesh == nullptr)return;
    if (gameObject == nullptr)return;
    if (transform == nullptr)return;

    auto device = RenderManager::GetDevice();
    RenderManager::LockDevice();
    
    world._11 = radius;
    world._22 = radius;
    world._33 = radius;

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

    device->SetTexture(0, 0);
    pMesh->DrawSubset(0);
    //device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, pMesh->GetNumVertices(), 0, pMesh->GetNumFaces());


    device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
    device->SetRenderState(D3DRS_LIGHTING, false);
    //device->SetFVF(originFVF);
    RenderManager::UnlockDevice();
}

IComponent* Engine::SphereCollider::Clone()
{
    return new SphereCollider(*this);
}

bool Engine::SphereCollider::Raycast(Ray ray, RaycastHit* outHitInfo, float maxDistance)
{
    // c = center of Sphere
    Vector3 worldCenter = GetWorldPosition();
    // p0 - c
    Vector3 v = ray.origin - worldCenter;

    // 판별식
    // -B +- sqrt(B*B - 4C) / 2
    // 안맞으면 둘다 음수
    // 안에 있다가 나가면 양수,음수
    // 밖에 있다가 안으로 들어가면 음수,양수
    // 관통하면 둘다 양수
    // 구면과 교차하면 둘다 양수이고, 둘은 같음

    // 광선(t) = 광선위치(p0) + t * 광선방향(u) 
    // p(t) = p0 + tu

    // B = 2(u * (p0 -c))
    float b = 2.0f * Vector3::Dot(ray.direction, v);
    // C = (p0-c)*(p0-c) - r^2
    float c = Vector3::Dot(v, v) - (radius * radius);

    // 판별식
    float discriminant = (b * b) - (4.0f * c);
    // 가상의 수 테스트
    if (discriminant < 0.f)
        return false;

    discriminant = sqrtf(discriminant);

    float t0 = (-b + discriminant) * 0.5f;
    float t1 = (-b - discriminant) * 0.5f;

    // 해가 >= 0 일 경우 교차
    if (t0 >= 0.f || t1 >= 0.f)
    {
        if (outHitInfo != nullptr)
        {
            // origin과 가장 가까운 t를 구함
            float nearT = min(fabsf(t0), fabsf(t1));
            // 광선(t) = 광선위치(p0) + t * 광선방향(u) 
            // p(t) = p0 + tu
            outHitInfo->point = ray.origin + nearT * ray.direction;
            outHitInfo->distance = Vector3::Distance(ray.origin, outHitInfo->point);
            outHitInfo->collider = this;
        }
        return true;
    }


    return false;
}

void Engine::SphereCollider::SetRadius(float _radius)
{
    radius = _radius;
    //transform->scale.x = _radius;
    //transform->scale.y = _radius;
    //transform->scale.z = _radius;
}

float Engine::SphereCollider::GetRadius()
{
    return radius;
}
