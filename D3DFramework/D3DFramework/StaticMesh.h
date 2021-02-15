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
        virtual Vector3* GetVertices() override { return this->pVertices; }
        virtual DWORD* GetIndices() override { return this->pIndices; }
        virtual ULONG GetVertexCount() override { return this->vertexCount; }
        virtual ULONG GetVertexSize() override { return this->vertexSize; }
        virtual ULONG GetFaceCount() override { return this->triangleCount; }

        int GetSubsetCount();
        IDirect3DTexture9* GetSubsetTexture(int index);
    public:
        HRESULT LoadMesh(const WCHAR* pFilePath, const WCHAR* pFileName);
        virtual void Render() override;
        void RenderSubset(int index);
    protected:
        void RenderUsingFixedPL();
        void RenderUsingShader();
    private:
        LPD3DXMESH			pOriginMesh;	// 최초 로드 시점에 생성하는 메쉬 컴객체
        LPD3DXMESH			pMesh; // 노말 정보를 삽입하여 변환시킨 메쉬 컴객체

        LPD3DXBUFFER		pAdjacency; // 인접한 이웃의 정보를 접근하기 위해 첫번째 주소를 보관하려는 멤버 변수
        LPD3DXBUFFER		pSubset; // 서브셋 개수 == 텍스쳐의 개수 == 재질의 개수
        D3DXMATERIAL*       pMaterial;
        ULONG				subsetCount;

        LPDIRECT3DTEXTURE9* ppTextures;

        // VertexSize (정점 메모리 크기)
        ULONG				vertexSize = 0;
        ULONG				vertexCount = 0;
        Vector3* pVertices;// = nullptr;
        DWORD* pIndices;// = nullptr;
        ULONG triangleCount = 0;
        DWORD fvf;



    };

}

