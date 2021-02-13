#pragma once
#include "RenderTarget.h"
#include <wrl.h>
using namespace Microsoft::WRL;
class RenderTargetImpl : public RenderTarget
{
public:
	RenderTargetImpl(int width, int height, D3DFORMAT fmt);
	virtual HRESULT GetSurface(IDirect3DSurface9** out) override;
	virtual HRESULT GetTexture(IDirect3DTexture9** out) override;
	ComPtr<IDirect3DTexture9> texture_;
	ComPtr<IDirect3DSurface9> surface_;
};