#pragma once
#include"GameRenderer.h"
#include<map>
#include<wrl.h>
#include<list>
using namespace Microsoft::WRL;
class GameRendererImpl : public GameRenderer
{
public:
	GameRendererImpl();
	void Register(RenderGroupID groupId, PKH::GameObject* object);
	void Unregister(RenderGroupID groupId, PKH::GameObject* object);
	void Render();
	void AddLight(const wchar_t* name, D3DLIGHT9 const& init);
	D3DLIGHT9* GetLight(const wchar_t* name);
	void RemoveLight(const wchar_t* name);
	virtual HRESULT GetEffect(const wchar_t* id, ID3DXEffect** effect) override;
protected:
	void DeferredRender();
	void DeferredLighting();
	void DeferredCombine();
	void RenderUI();
	void RenderHUD();
private:
	Matrix													mViewProj;
	ComPtr<ID3DXEffect>										deferredShader_;
	ComPtr<IDirect3DIndexBuffer9>							indexBuffer_;
	ComPtr<IDirect3DVertexBuffer9>							vertexBuffer_;
	std::map<std::wstring, ComPtr<ID3DXEffect> >			effects_;
	std::map<RenderGroupID, std::list<PKH::GameObject* > >	renderGroups_;
	std::map<std::wstring, D3DLIGHT9>						lights_;
};