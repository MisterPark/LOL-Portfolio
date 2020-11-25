#pragma once
#include "Mesh.h"

namespace PKH
{
	class DynamicMesh : public Mesh
	{
	public:
		explicit DynamicMesh(GameObject* owner);
		explicit DynamicMesh(const DynamicMesh& rhs);
		virtual ~DynamicMesh();
		// Mesh을(를) 통해 상속됨
		virtual IComponent * Clone() override;
	public:
		HRESULT			Ready_Meshes(const WCHAR* pFilePath, const WCHAR* pFileName);
		void			Render_Meshes(void);
		const  D3DXFRAME_DERIVED* Get_FrameByName(const char* pFrameName);
		bool							Is_AnimationSetEnd(void);
	public:
		void			Set_AnimationSet(const UINT& iIndex);
		void			Play_Animation(const float& fTimeDelta);

	private:

		// 모든 뼈들을 순회하면서 뼈들이 갖고 있는 TransformationMatrix와 pParentMatrix를 결합하여 CombinedTransformationMatrix를 만들어주는 함수
		void			Update_FrameMatrices(D3DXFRAME_DERIVED* pFrame, const Matrix* pParentMatrix);

		// CombinedTransformationMatrix의 주소값을 얻어와서 채워주는 함수
		void			SetUp_FrameMatrixPointer(D3DXFRAME_DERIVED* pFrame);

	private:
		D3DXFRAME* m_pRootFrame;
		HierarchyLoader* m_pLoader;
		AnimationController* m_pAniCtrl;
		list<D3DXMESHCONTAINER_DERIVED*>			m_MeshContainerList;

	};
}


