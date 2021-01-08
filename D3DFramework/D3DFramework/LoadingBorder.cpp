#include "stdafx.h"
#include "LoadingBorder.h"

LoadingBorder::LoadingBorder()
{
	SetTexture(L"loadingFrameBlue");
	mesh->SetBlendMode(BlendMode::ALPHA_BLEND);

}

LoadingBorder::~LoadingBorder()
{
}

void LoadingBorder::Initialize()
{
}

void LoadingBorder::Release()
{
}
