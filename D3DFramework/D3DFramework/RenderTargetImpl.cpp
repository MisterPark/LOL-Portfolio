#include "stdafx.h"
#include "RenderTargetImpl.h"
#include "RenderManager.h"
RenderTargetImpl::RenderTargetImpl(int width, int height, D3DFORMAT fmt)
{
    HRESULT hr = E_FAIL;
    IDirect3DDevice9* device = RenderManager::GetDevice();
    hr = device->CreateTexture(
        width,
        height,
        1,
        D3DUSAGE_RENDERTARGET,
        fmt,
        D3DPOOL_DEFAULT,
        &texture_,
        nullptr);
    if (FAILED(hr))
    {
        throw hr;
    }
    texture_->GetSurfaceLevel(0, &surface_);
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