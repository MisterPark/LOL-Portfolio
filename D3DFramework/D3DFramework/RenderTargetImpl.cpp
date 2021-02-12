#include "stdafx.h"
#include "RenderTargetImpl.h"

RenderTargetImpl::RenderTargetImpl(int width, int height, D3DFORMAT fmt)
{
}

HRESULT RenderTargetImpl::GetSurface(IDirect3DSurface9** out)
{
    if (out == nullptr)
    {
        return E_POINTER;
    }
    *out = surface_.Get();
    surface_->AddRef();
    return S_OK;
}

HRESULT RenderTargetImpl::GetTexture(IDirect3DTexture9** out)
{
    if (out == nullptr)
    {
        return E_POINTER;
    }
    *out = texture_.Get();
    texture_->AddRef();
    return S_OK;
}
