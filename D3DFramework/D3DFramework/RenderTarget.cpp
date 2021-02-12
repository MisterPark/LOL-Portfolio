#include "stdafx.h"
#include "RenderTarget.h"
#include "RenderTargetImpl.h"
HRESULT RenderTarget::Create(int width, int height, D3DFORMAT fmt, RenderTarget** out)
{
    if (out == nullptr)
    {
        return E_POINTER;
    }
    try
    {
        RenderTargetImpl renderTarget{ width, height, fmt };
        *out = new RenderTargetImpl{ std::move(renderTarget) };
    }
    catch (...)
    {
        return E_FAIL;
    }
    return S_OK;
}
