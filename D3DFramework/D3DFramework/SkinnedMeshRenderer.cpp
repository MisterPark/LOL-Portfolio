#include "stdafx.h"
#include "SkinnedMeshRenderer.h"
#include <wrl.h>
using namespace Microsoft::WRL;


KST::SkinnedMeshRenderer::SkinnedMeshRenderer(PKH::GameObject* owner):
	Renderer(owner, RendererType::Forward)
{

}

void KST::SkinnedMeshRenderer::Render()
{
	IDirect3DDevice9* device = RenderManager::GetDevice();
	ComPtr<IDirect3DSurface9> surface;
	device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &surface);
	device->SetRenderTarget(0, surface.Get());

	device->SetTransform(D3DTS_WORLD, &gameObject->transform->world);
	device->SetRenderState(D3DRS_LIGHTING, false);
	std::list<D3DXMESHCONTAINER_DERIVED*> const& meshContainers = this->mesh->GetMeshContainersRef();
	mesh->UpdateFrame();
	for (auto& iter : meshContainers)
	{
		D3DXMESHCONTAINER_DERIVED* pMeshContainer = iter;

		for (ULONG i = 0; i < pMeshContainer->dwNumBones; ++i)
		{
			pMeshContainer->pRenderingMatrix[i] = pMeshContainer->pFrameOffsetMatrix[i] * (*pMeshContainer->ppFrameCombinedMatrix[i]);
		}

		void* pSrcVtx = nullptr;
		void* pDestVtx = nullptr;


		pMeshContainer->pOriMesh->LockVertexBuffer(0, &pSrcVtx);
		pMeshContainer->MeshData.pMesh->LockVertexBuffer(0, &pDestVtx);

		// 소프트웨어 스키닝을 수행하는 함수(스키닝 뿐 아니라 애니메이션 변경 시, 뼈대들과 정점 정보들의 변경을 동시에 수행하기도 함)
		pMeshContainer->pSkinInfo->UpdateSkinnedMesh(pMeshContainer->pRenderingMatrix,	// 최종 뼈의 변환상태 행렬
			nullptr,						// 원래 상태로 되돌리기 위한 상태 행렬(원래는 위 행렬의 역행렬을 구해서 넣어줘야 하지만 안넣어줘도 상관 없음)
			pSrcVtx,						// 변하지 않는 원본 메쉬의 정점 정보
			pDestVtx);						// 변환된 정보를 담기 위한 메쉬의 정점 정보
		pMeshContainer->pOriMesh->UnlockVertexBuffer();
		pMeshContainer->MeshData.pMesh->UnlockVertexBuffer();

		for (ULONG i = 0; i < pMeshContainer->NumMaterials; ++i)
		{
			device->SetTexture(0, pMeshContainer->ppTexture[i]);
			pMeshContainer->MeshData.pMesh->DrawSubset(i);
		}
	}
}

void KST::SkinnedMeshRenderer::SetMesh(DynamicMesh* mesh)
{
	this->mesh = mesh;
}
