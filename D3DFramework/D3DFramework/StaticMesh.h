#pragma once
#include "Mesh.h"

namespace PKH
{
    class StaticMesh : public Mesh
    {
    public:
        explicit StaticMesh(GameObject* owner);
        explicit StaticMesh(const StaticMesh& rhs);
        virtual ~StaticMesh();

    public:
        virtual IComponent* Clone() override;

    public:
        const ULONG& GetVertexCount() { return this->vertexCount; }
        const ULONG& GetVertexSize() { return this->vertexSize; }
        const Vector3* GetVertices() { return this->pVertices; }

    public:
        HRESULT LoadMesh(const WCHAR* pFilePath, const WCHAR* pFileName);
        void Render();

    private:
        LPD3DXMESH			pOriginMesh;	// 최초 로드 시점에 생성하는 메쉬 컴객체
        LPD3DXMESH			pMesh; // 노말 정보를 삽입하여 변환시킨 메쉬 컴객체

        LPD3DXBUFFER		pAdjacency; // 인접한 이웃의 정보를 접근하기 위해 첫번째 주소를 보관하려는 멤버 변수
        LPD3DXBUFFER		pSubset; // 서브셋 개수 == 텍스쳐의 개수 == 재질의 개수
        D3DXMATERIAL*       pMaterial;
        ULONG				subsetCount;

        // VertexSize (정점 메모리 크기)
        ULONG				vertexSize;
        ULONG				vertexCount;
        Vector3*            pVertices;

        LPDIRECT3DTEXTURE9* ppTextures;
    };

}

