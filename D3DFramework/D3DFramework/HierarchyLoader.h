#pragma once
#include <d3dx9anim.h>

namespace PKH
{
	class HierarchyLoader : public ID3DXAllocateHierarchy
	{
	private:
		explicit HierarchyLoader(LPDIRECT3DDEVICE9 pGraphicDev, const WCHAR* pPath);
		virtual ~HierarchyLoader(void);

	public:
		STDMETHOD(CreateFrame)(THIS_ LPCSTR Name, LPD3DXFRAME* ppNewFrame);

		STDMETHOD(CreateMeshContainer)(THIS_ LPCSTR Name,
			CONST D3DXMESHDATA* pMeshData,
			CONST D3DXMATERIAL* pMaterials,
			CONST D3DXEFFECTINSTANCE* pEffectInstances,
			DWORD NumMaterials,
			CONST DWORD* pAdjacency,
			LPD3DXSKININFO pSkinInfo,
			LPD3DXMESHCONTAINER* ppNewMeshContainer);


		STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME pFrameToFree);

		STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree);

	private:
		void		Allocate_Name(char** ppName, const char* pFrameName);

	private:
		LPDIRECT3DDEVICE9				m_pGraphicDev;
		const WCHAR* m_pPath;

	public:
		static HierarchyLoader* Create(LPDIRECT3DDEVICE9 pGraphicDev, const WCHAR* pPath);
	public:
		ULONG	Release(void);
	};

}

