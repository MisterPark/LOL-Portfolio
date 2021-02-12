#pragma once
#include<d3d9.h>
class RenderTarget
{
public:
	virtual ~RenderTarget() = default;
	
	static HRESULT Create(int width, int height, D3DFORMAT fmt, RenderTarget** out);

	virtual HRESULT GetSurface(IDirect3DSurface9** out) = 0;
	virtual HRESULT GetTexture(IDirect3DTexture9** out) = 0;
};