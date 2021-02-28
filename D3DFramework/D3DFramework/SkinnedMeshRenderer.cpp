#include "stdafx.h"
#include "SkinnedMeshRenderer.h"
#include <wrl.h>
using namespace Microsoft::WRL;


Engine::SkinnedMeshRenderer::SkinnedMeshRenderer(Engine::GameObject* owner):
	Renderer(owner, RendererType::Deferred)
{
	albedoRenderTarget = RenderManager::GetRenderTarget(RENDER_TARGET_ALBEDO);
	normalRenderTarget = RenderManager::GetRenderTarget(RENDER_TARGET_NORMAL);
	sharpnessRenderTarget = RenderManager::GetRenderTarget(RENDER_TARGET_SHARPNESS);
	rimLightRenderTarget = RenderManager::GetRenderTarget(RENDER_TARGET_RIMLIGHT_COLOR);
	renderingShader = RenderManager::LoadEffect(L"./deferred_render.fx");
	shadowMapShader = RenderManager::LoadEffect(L"./shadow_map_shader.fx");
	rimLightColor = Vector3{ 0.f, 0.f, 0.f };
}

void Engine::SkinnedMeshRenderer::Render()
{

	IDirect3DDevice9* device = RenderManager::GetDevice();

	std::list<D3DXMESHCONTAINER_DERIVED*> const& meshContainers = this->mesh->GetMeshContainersRef();
	mesh->UpdateFrame();

	Vector3 worldPos = *((Vector3*)&transform->worldMatrix._41);

	// TODO : Render 반경 계산 해야할듯?
	if (Frustum::Intersect(&worldPos, 1.f) == false) return;

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
		RenderShadowMap(pMeshContainer);
		RenderGBuffer(pMeshContainer);
	}
}

void Engine::SkinnedMeshRenderer::SetMesh(DynamicMesh* mesh)
{
	this->mesh = mesh;
}

void Engine::SkinnedMeshRenderer::EnableRimLight(Vector3 const& color)
{
	rimLightEnable = true;
	rimLightColor = color;
}

void Engine::SkinnedMeshRenderer::DisableRimLight()
{
	rimLightEnable = false;
	rimLightColor = Vector3(0.f, 0.f, 0.f);
}

void Engine::SkinnedMeshRenderer::RenderShadowMap(D3DXMESHCONTAINER_DERIVED* container)
{
	IDirect3DDevice9* device = RenderManager::GetDevice();

	ID3DXMesh* mesh = container->MeshData.pMesh;
	int subsetCount = container->NumMaterials;

	const int lightCount = RenderSystem::GetLightCount();
	std::vector<const std::wstring*> lightNames;

	lightNames.reserve(RenderSystem::GetLightCount());
	for (int i = 0; i < lightCount; ++i)
	{
		lightNames.push_back(&RenderSystem::GetLightName(i));
	}
	UINT passCount = 0;
	UINT passNum = 0;
	shadowMapShader->Begin(&passCount, 0);
	shadowMapShader->BeginPass(passNum);
	ComPtr<IDirect3DSurface9> oldSurface;
	device->GetDepthStencilSurface(&oldSurface);
	for (auto lightNamePtr : lightNames)
	{
		ComPtr<IDirect3DSurface9> depthBuffer;
		ComPtr<IDirect3DSurface9> surface;
		ComPtr<IDirect3DSurface9> optionSurface;

		RenderTarget* renderTarget;
		Matrix projMatrix;

		if (!RenderSystem::GetShadowMap(lightNamePtr->c_str(), &renderTarget,  &depthBuffer, &projMatrix))
		{
			continue;
		}
		renderTarget->GetSurface(&surface);
		shadowMapShader->SetMatrix("g_mCameraProj", &projMatrix);
		shadowMapShader->SetMatrix("g_mWorld", &transform->worldMatrix);
		shadowMapShader->SetBool("g_shadow", true);
		shadowMapShader->CommitChanges();
		device->SetRenderTarget(0, surface.Get());
		device->SetRenderTarget(1, optionSurface.Get());
		device->SetRenderTarget(2, nullptr);
		device->SetRenderTarget(3, nullptr);
		device->SetDepthStencilSurface(depthBuffer.Get());
		
		for (int i = 0; i < subsetCount; ++i)
		{
			mesh->DrawSubset(i);
		}

	}
	shadowMapShader->EndPass();
	shadowMapShader->End();
	device->SetDepthStencilSurface(oldSurface.Get());

}

void Engine::SkinnedMeshRenderer::RenderGBuffer(D3DXMESHCONTAINER_DERIVED* container)
{
	Vector3 worldPos = *((Vector3*)&transform->worldMatrix._41);

	// TODO : Render 반경 계산 해야할듯?
	if (Frustum::Intersect(&worldPos, 1.f) == false) return;

	IDirect3DDevice9* device = RenderManager::GetDevice();
	ComPtr<IDirect3DSurface9> albedoSurface;
	ComPtr<IDirect3DSurface9> normalSurface;
	ComPtr<IDirect3DSurface9> sharpnessSurface;
	ComPtr<IDirect3DSurface9> rimLightSurface;
	
	albedoRenderTarget->GetSurface(&albedoSurface);
	normalRenderTarget->GetSurface(&normalSurface);
	sharpnessRenderTarget->GetSurface(&sharpnessSurface);
	rimLightRenderTarget->GetSurface(&rimLightSurface);

	device->SetRenderTarget(0, albedoSurface.Get());
	device->SetRenderTarget(1, normalSurface.Get());
	device->SetRenderTarget(2, sharpnessSurface.Get());
	device->SetRenderTarget(3, rimLightSurface.Get());
	//device->Clear(0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_COLORVALUE(0.f, 0.f, 0.f, 0.f), 1.f, 0);
	UINT passCount = 0;
	UINT passNum = 0;

	Matrix mViewSpace = Camera::main->GetViewMatrix();
	Matrix mProjSpace = Camera::main->GetProjectionMatrix();
	Matrix mViewProj = mViewSpace * mProjSpace;
	renderingShader->SetMatrix("g_mViewSpace", &mViewSpace);
	renderingShader->SetMatrix("g_mProjSpace", &mProjSpace);
	renderingShader->SetMatrix("g_mViewProj", &mViewProj);
	renderingShader->SetMatrix("g_mView", &mViewSpace);
	renderingShader->SetMatrix("g_mWorld", &transform->worldMatrix);
	D3DXVECTOR4 rimLightColor{ this->rimLightColor };
	rimLightColor.w = 1.f;
	renderingShader->SetVector("g_vRimLightColor", &rimLightColor);
	renderingShader->Begin(&passCount, 0);
	renderingShader->BeginPass(passNum);
	for (ULONG i = 0; i < container->NumMaterials; ++i)
	{
		IDirect3DTexture9* texture = container->ppTexture[i];
		renderingShader->SetTexture("g_diffuseTexture", texture);
		renderingShader->CommitChanges();
		container->MeshData.pMesh->DrawSubset(i);
	}
	renderingShader->EndPass();
	renderingShader->End();
}
