#include "stdafx.h"
#include "DynamicMesh.h"
#include "HierarchyLoader.h"
#include "AnimationController.h"
#include "GameRenderer.h"
PKH::DynamicMesh::DynamicMesh(GameObject* owner)
	:Mesh(owner)
	, m_pRootFrame(nullptr)
	, m_pLoader(nullptr)
	, m_pAniCtrl(nullptr)
{
	type = MeshType::DYNAMIC_MESH;

}

PKH::DynamicMesh::DynamicMesh(const DynamicMesh& rhs)
	:Mesh(rhs)
	, m_pRootFrame(rhs.m_pRootFrame)
	, m_pLoader(rhs.m_pLoader)
	, m_MeshContainerList(rhs.m_MeshContainerList)
	, m_AnimKeys(rhs.m_AnimKeys)
{
	//CloneFrame((D3DXFRAME_DERIVED*)rhs.m_pRootFrame, &m_pRootFrame);
	//Matrix		matTemp;// = Matrix::identity;
	//D3DXMatrixRotationY(&matTemp, D3DXToRadian(180.f));
	//UpdateFrameMatrices((D3DXFRAME_DERIVED*)m_pRootFrame, &matTemp);

	//SetUpFrameMatrixPointer((D3DXFRAME_DERIVED*)m_pRootFrame);
	m_pAniCtrl = AnimationController::Create(*rhs.m_pAniCtrl);
}

PKH::DynamicMesh::~DynamicMesh()
{
	Safe_Release(&m_pAniCtrl);

	if (false == isClone)
	{
		m_pLoader->DestroyFrame(m_pRootFrame);
		Safe_Release(&m_pLoader);
	}
	else
	{
		//DeleteFrame(m_pRootFrame);
	}
	m_MeshContainerList.clear();
}

IComponent * PKH::DynamicMesh::Clone()
{
	return new DynamicMesh(*this);
}

HRESULT DynamicMesh::LoadMesh(const WCHAR* pFilePath, const WCHAR* pFileName)
{
	WCHAR		szFullPath[256] = L"";

	lstrcpy(szFullPath, pFilePath);
	lstrcat(szFullPath, pFileName);

	device = RenderManager::GetDevice();
	m_pLoader = HierarchyLoader::Create(device, pFilePath);
	NULL_CHECK_RETURN(m_pLoader, E_FAIL);

	LPD3DXANIMATIONCONTROLLER		pAniCtrl = nullptr;

	FAILED_CHECK_RETURN(D3DXLoadMeshHierarchyFromX(szFullPath,
		D3DXMESH_MANAGED,
		device,
		m_pLoader,	// HierarchyLoader
		NULL,
		&m_pRootFrame,
		&pAniCtrl),	// AniCtrl
		E_FAIL);

	m_pAniCtrl = AnimationController::Create(pAniCtrl);
	NULL_CHECK_RETURN(m_pAniCtrl, E_FAIL);

	Safe_Release(&pAniCtrl);

	Matrix		matTemp;// = Matrix::identity;
	D3DXMatrixRotationY(&matTemp, D3DXToRadian(180.f));
	UpdateFrameMatrices((D3DXFRAME_DERIVED*)m_pRootFrame, &matTemp);

	SetUpFrameMatrixPointer((D3DXFRAME_DERIVED*)m_pRootFrame);


	UINT animCount = m_pAniCtrl->GetNumAnimations();
	for (UINT i = 0; i < animCount; i++)
	{
		char* name;
		string str;

		if (m_pAniCtrl->GetAnimationName(&name, i))
		{
			str = name;
			if (str == "w_go")
			{
				str = "w2";
			}
			else if (str == "q_go")
			{
				str = "q2";
			}
			else if (str == "spell1")
			{
				str = "q";
			}
			else if (str == "spell2")
			{
				str = "w";
			}
			else if (str == "spell3")
			{
				str = "e";
			}
			else if (str == "spell4")
			{
				str = "q";
			}
			else if (str == "recall1")
			{
				str = "recall";
			}

			m_AnimKeys[str] = i;
		}
	}

	return S_OK;
}

void DynamicMesh::Render(void)
{
	if (gameObject == nullptr)return;
	

	if (stopFlag == true)
	{
		animSpeed = 0.f;
	}
	PlayAnimation(animSpeed);
	animSpeed = 0.f;
		
	//RenderManager::GetDevice()->SetTransform(D3DTS_WORLD, &gameObject->transform->world);

	Matrix		matTemp = gameObject->transform->world;
	//D3DXMatrixRotationY(&matTemp, D3DXToRadian(180.f));
	matTemp._41 = 0.f;
	matTemp._42 = 0.f;
	matTemp._43 = 0.f;
	//UpdateFrameMatrices((D3DXFRAME_DERIVED*)m_pRootFrame, &);
	UpdateFrameMatrices((D3DXFRAME_DERIVED*)m_pRootFrame, &matTemp);

	if (renderGroupID == RenderGroupID::Deferred)
	{
		RenderUsingShader();
	}
	else
	{
		RenderUsingFixedPL();
	}
}

void PKH::DynamicMesh::UpdateFrame()
{
	if (gameObject == nullptr)return;


	if (stopFlag == true)
	{
		animSpeed = 0.f;
	}
	PlayAnimation(animSpeed);
	animSpeed = 0.f;

	//RenderManager::GetDevice()->SetTransform(D3DTS_WORLD, &gameObject->transform->world);

	Matrix		matTemp = gameObject->transform->world;
	//D3DXMatrixRotationY(&matTemp, D3DXToRadian(180.f));
	matTemp._41 = 0.f;
	matTemp._42 = 0.f;
	matTemp._43 = 0.f;
	//UpdateFrameMatrices((D3DXFRAME_DERIVED*)m_pRootFrame, &);
	UpdateFrameMatrices((D3DXFRAME_DERIVED*)m_pRootFrame, &matTemp);
}

const list<D3DXMESHCONTAINER_DERIVED*>& PKH::DynamicMesh::GetMeshContainersRef()
{
	return m_MeshContainerList;
}

void PKH::DynamicMesh::RenderUsingFixedPL()
{
	device = RenderManager::GetDevice();
	device->SetTransform(D3DTS_WORLD, &gameObject->transform->world);
	device->SetRenderState(D3DRS_LIGHTING, false);
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	for (auto& iter : m_MeshContainerList)
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

		RenderManager::LockDevice();

		for (ULONG i = 0; i < pMeshContainer->NumMaterials; ++i)
		{
			device->SetTexture(0, pMeshContainer->ppTexture[i]);
			pMeshContainer->MeshData.pMesh->DrawSubset(i);
		}

		RenderManager::UnlockDevice();

	}
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	device->SetRenderState(D3DRS_LIGHTING, false);
}

void PKH::DynamicMesh::RenderUsingShader()
{

	GameRenderer* renderer = GameRenderer::Instance();
	ID3DXEffect* effect = nullptr;
	UINT passCount = 0;
	renderer->GetEffect(L"DEFERRED", &effect);
	effect->SetMatrix("g_mWorld", &gameObject->transform->world);
	device = RenderManager::GetDevice();
	effect->Begin(&passCount, 0);
	effect->BeginPass(0);
	for (auto& iter : m_MeshContainerList)
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

		RenderManager::LockDevice();

		for (ULONG i = 0; i < pMeshContainer->NumMaterials; ++i)
		{
			effect->SetTexture("g_diffuseTexture", pMeshContainer->ppTexture[i]);
			effect->CommitChanges();
			pMeshContainer->MeshData.pMesh->DrawSubset(i);
		}


		RenderManager::UnlockDevice();
	}
	effect->EndPass();
	effect->End();
}

const D3DXFRAME_DERIVED* DynamicMesh::GetFrameByName(const char* pFrameName)
{
	return (D3DXFRAME_DERIVED*)D3DXFrameFind(m_pRootFrame, pFrameName);
}

bool DynamicMesh::IsAnimationSetEnd(void)
{
	return m_pAniCtrl->IsAnimationSetEnd();
}

void DynamicMesh::SetAnimationSet(const UINT& iIndex)
{
	m_pAniCtrl->SetAnimationSet(iIndex);
}

void PKH::DynamicMesh::SetAnimationSet(const char* name)
{
	auto end = m_AnimKeys.end();
	auto find = m_AnimKeys.find(name);
	if (find != end)
	{
		m_pAniCtrl->SetAnimationSet(find->second);
	}
	else
	{
		m_pAniCtrl->SetAnimationSet(0);
	}
}

void DynamicMesh::PlayAnimation(const float& fTimeDelta)
{
	m_pAniCtrl->PlayAnimation(fTimeDelta);

	
}

bool PKH::DynamicMesh::GetAnimationIndex(UINT* outIndex, const char* name)
{
	auto end = m_AnimKeys.end();
	auto find = m_AnimKeys.find(name);
	if (find != end)
	{
		*outIndex = find->second;
		return true;
	}
	*outIndex = 0;
	return false;
}

double PKH::DynamicMesh::GetPeriod(const UINT& index)
{
	return m_pAniCtrl->GetPeriod(index);
}

void DynamicMesh::UpdateFrameMatrices(D3DXFRAME_DERIVED* pFrame, const Matrix* pParentMatrix)
{
	if (nullptr == pFrame)
		return;

	pFrame->CombinedTransformationMatrix = pFrame->TransformationMatrix * (*pParentMatrix);

	if (nullptr != pFrame->pFrameSibling)
		UpdateFrameMatrices((D3DXFRAME_DERIVED*)pFrame->pFrameSibling, pParentMatrix);

	if (nullptr != pFrame->pFrameFirstChild)
		UpdateFrameMatrices((D3DXFRAME_DERIVED*)pFrame->pFrameFirstChild, &pFrame->CombinedTransformationMatrix);

}

void DynamicMesh::SetUpFrameMatrixPointer(D3DXFRAME_DERIVED* pFrame)
{
	if (nullptr != pFrame->pMeshContainer)
	{
		D3DXMESHCONTAINER_DERIVED* pDerivedMeshContainer = (D3DXMESHCONTAINER_DERIVED*)pFrame->pMeshContainer;

		for (ULONG i = 0; i < pDerivedMeshContainer->dwNumBones; ++i)
		{
			const char* pBoneName = pDerivedMeshContainer->pSkinInfo->GetBoneName(i);
			D3DXFRAME_DERIVED* pBone = (D3DXFRAME_DERIVED*)D3DXFrameFind(m_pRootFrame, pBoneName);

			pDerivedMeshContainer->ppFrameCombinedMatrix[i] = &pBone->CombinedTransformationMatrix;
		}

		m_MeshContainerList.push_back(pDerivedMeshContainer);
	}

	if (nullptr != pFrame->pFrameSibling)
		SetUpFrameMatrixPointer((D3DXFRAME_DERIVED*)pFrame->pFrameSibling);

	if (nullptr != pFrame->pFrameFirstChild)
		SetUpFrameMatrixPointer((D3DXFRAME_DERIVED*)pFrame->pFrameFirstChild);

}

void PKH::DynamicMesh::CloneFrame(D3DXFRAME_DERIVED* pRoot, D3DXFRAME** ppOutCloneFrame)
{
	if (nullptr == pRoot) return;
	if (ppOutCloneFrame == nullptr) return;

	D3DXFRAME_DERIVED* frame = new D3DXFRAME_DERIVED;
	frame->Name = pRoot->Name;
	frame->TransformationMatrix = pRoot->TransformationMatrix;
	frame->pMeshContainer = pRoot->pMeshContainer;
	//frame->CombinedTransformationMatrix = pRoot->CombinedTransformationMatrix;
	frame->pFrameSibling = nullptr;
	frame->pFrameFirstChild = nullptr;
	(*ppOutCloneFrame) = frame;


	if (nullptr != pRoot->pFrameSibling)
		CloneFrame((D3DXFRAME_DERIVED*)pRoot->pFrameSibling, &frame->pFrameSibling);

	if (nullptr != pRoot->pFrameFirstChild)
		CloneFrame((D3DXFRAME_DERIVED*)pRoot->pFrameFirstChild, &frame->pFrameFirstChild);

}

void PKH::DynamicMesh::DeleteFrame(D3DXFRAME* pRoot)
{
	if (nullptr == pRoot)
		return;
	
	if (nullptr != pRoot->pFrameFirstChild)
	{
		DeleteFrame(pRoot->pFrameFirstChild);
	}
	
	if (nullptr != pRoot->pFrameSibling)
	{
		DeleteFrame(pRoot->pFrameSibling);
	}

	delete pRoot;

}


