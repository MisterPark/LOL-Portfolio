#include "stdafx.h"
#include "LoadingChampPanel.h"

LoadingChampPanel::LoadingChampPanel()
{
	SetTexture(L"garenloadscreen");
	mesh->SetBlendMode(BlendMode::ALPHA_BLEND);
}

LoadingChampPanel::~LoadingChampPanel()
{
}

void LoadingChampPanel::Initialize()
{
}

void LoadingChampPanel::Release()
{
}
