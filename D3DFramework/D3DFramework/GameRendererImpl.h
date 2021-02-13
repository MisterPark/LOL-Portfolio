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
	void Register(RenderComponent* mesh);
	void Unregister(RenderComponent* mesh);
	void Render();
	void AddLight(const wchar_t* name, D3DLIGHT9 const& init);
	D3DLIGHT9* GetLight(const wchar_t* name);
	void RemoveLight(const wchar_t* name);
	virtual HRESULT GetEffect(const wchar_t* id, ID3DXEffect** effect) override;
protected:
	void DeferredRender();
	void DeferredLighting();
	void DeferredCombine();
	void RenderAlphaForward();
	void RenderUI();
	void RenderHUD();
	void RenderDebugRT();
private:
	Matrix													mViewProj;
	ComPtr<ID3DXSprite>										sprite_;
	ComPtr<ID3DXEffect>										deferredShader_;
	ComPtr<IDirect3DIndexBuffer9>							indexBuffer_;
	ComPtr<IDirect3DVertexBuffer9>							vertexBuffer_;
	std::map<std::wstring, ComPtr<ID3DXEffect> >			effects_;
	std::map<std::wstring, D3DLIGHT9>						lights_;

	std::map<RenderGroupID, std::list<RenderComponent* > >	renderGroups_;
};