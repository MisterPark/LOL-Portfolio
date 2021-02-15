#pragma once
#include "Mesh.h"

namespace PKH
{
	class HierarchyLoader;
	class AnimationController;
	
	class DynamicMesh : public Mesh
	{
	public:
		explicit DynamicMesh(GameObject* owner);
		explicit DynamicMesh(const DynamicMesh& rhs);
		virtual ~DynamicMesh();
		// Mesh을(를) 통해 상속됨
		virtual IComponent * Clone() override;
	public:
		HRESULT			LoadMesh(const WCHAR* pFilePath, const WCHAR* pFileName);
		//렌더링을 준비한다.
		void UpdateFrame();
		const list<D3DXMESHCONTAINER_DERIVED*>& GetMeshContainersRef();

		const  D3DXFRAME_DERIVED* GetFrameByName(const char* pFrameName);
		bool			IsAnimationSetEnd(void);
	public:
		void			SetAnimationSet(const UINT& iIndex);
		void			SetAnimationSet(const char* name);
		void			PlayAnimation(const float& fTimeDelta);

		bool			GetAnimationIndex(UINT* outIndex, const char* name);
		double			GetPeriod(const UINT& index);
	private:

		// 모든 뼈들을 순회하면서 뼈들이 갖고 있는 TransformationMatrix와 pParentMatrix를 결합하여 CombinedTransformationMatrix를 만들어주는 함수
		void			UpdateFrameMatrices(D3DXFRAME_DERIVED* pFrame, const Matrix* pParentMatrix);

		// CombinedTransformationMatrix의 주소값을 얻어와서 채워주는 함수
		void			SetUpFrameMatrixPointer(D3DXFRAME_DERIVED* pFrame);

		void			CloneFrame(D3DXFRAME_DERIVED* pRoot, D3DXFRAME** ppOutCloneFrame);
		void			DeleteFrame(D3DXFRAME* pRoot);
	public:
		// TODO : 이것들 세팅해줘야 할 경우가 생기려나?
		virtual ULONG GetVertexCount() override { return 0; }
		virtual ULONG GetVertexSize() override { return 0; }
		virtual Vector3* GetVertices() override { return nullptr; }
		virtual DWORD* GetIndices() override { return nullptr; }
		virtual ULONG GetFaceCount() override { return 0; }

	private:
		D3DXFRAME* m_pRootFrame;
		HierarchyLoader* m_pLoader;
		AnimationController* m_pAniCtrl;
		list<D3DXMESHCONTAINER_DERIVED*>			m_MeshContainerList;

		map<string, UINT> m_AnimKeys;
	public:
		float animSpeed = 0.f;
		bool stopFlag = false;

	};
}


