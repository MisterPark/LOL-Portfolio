#include "stdafx.h"
#include "LoadingPanel.h"

LoadingPanel::LoadingPanel()
{
	SetTexture(L"loadScreen");
	mesh->SetBlendMode(BlendMode::ALPHA_BLEND);
}

LoadingPanel::~LoadingPanel()
{
}

void LoadingPanel::Initialize()
{
}

void LoadingPanel::Release()
{
}
