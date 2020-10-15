#include "stdafx.h"
#include "SkyBox.h"
#include "Rectangle.h"

SkyBox* pSkyBox = nullptr;

PKH::SkyBox::SkyBox()
{
	isVisible = false;

	Mesh* mesh = (Mesh*)AddComponent<PKH::Rectangle>(L"F");
	mesh->SetTexture(TextureKey::SKY_F);
	mesh->SetVertexPos(0, Vector3(-350, -350, 350));
	mesh->SetVertexPos(1, Vector3(-350, 350, 350));
	mesh->SetVertexPos(2, Vector3(350, 350, 350));
	mesh->SetVertexPos(3, Vector3(350, -350, 350));
	
	mesh = (Mesh*)AddComponent<PKH::Rectangle>(L"B");
	mesh->SetTexture(TextureKey::SKY_B);
	mesh->SetVertexPos(0, Vector3(350, -350, -350));
	mesh->SetVertexPos(1, Vector3(350, 350, -350));
	mesh->SetVertexPos(2, Vector3(-350, 350, -350));
	mesh->SetVertexPos(3, Vector3(-350, -350, -350));

	mesh = (Mesh*)AddComponent<PKH::Rectangle>(L"L");
	mesh->SetTexture(TextureKey::SKY_L);
	mesh->SetVertexPos(0, Vector3(-350, -350, -350));
	mesh->SetVertexPos(1, Vector3(-350, 350, -350));
	mesh->SetVertexPos(2, Vector3(-350, 350, 350));
	mesh->SetVertexPos(3, Vector3(-350, -350, 350));

	mesh = (Mesh*)AddComponent<PKH::Rectangle>(L"R");
	mesh->SetTexture(TextureKey::SKY_R);
	mesh->SetVertexPos(0, Vector3(350, -350, 350));
	mesh->SetVertexPos(1, Vector3(350, 350, 350));
	mesh->SetVertexPos(2, Vector3(350, 350, -350));
	mesh->SetVertexPos(3, Vector3(350, -350, -350));

	mesh = (Mesh*)AddComponent<PKH::Rectangle>(L"U");
	mesh->SetTexture(TextureKey::SKY_U);
	mesh->SetVertexPos(0, Vector3(-350, 350, 350));
	mesh->SetVertexPos(1, Vector3(-350, 350, -350));
	mesh->SetVertexPos(2, Vector3(350, 350, -350));
	mesh->SetVertexPos(3, Vector3(350, 350, 350));

	mesh = (Mesh*)AddComponent<PKH::Rectangle>(L"D");
	mesh->SetTexture(TextureKey::SKY_D);
	mesh->SetVertexPos(0, Vector3(-350, -350, -350));
	mesh->SetVertexPos(1, Vector3(-350, -350, 350));
	mesh->SetVertexPos(2, Vector3(350, -350, 350));
	mesh->SetVertexPos(3, Vector3(350, -350, -350));
}

PKH::SkyBox::~SkyBox()
{
}

SkyBox* PKH::SkyBox::GetInstance()
{
	if (pSkyBox == nullptr)
	{
		pSkyBox = new SkyBox();
	}
	return pSkyBox;
}

void PKH::SkyBox::Destroy()
{
	if (pSkyBox)
	{
		delete pSkyBox;
		pSkyBox = nullptr;
	}
}

void PKH::SkyBox::Show()
{
	pSkyBox->isVisible = true;
}

void PKH::SkyBox::Hide()
{
	pSkyBox->isVisible = false;
}

void PKH::SkyBox::Update()
{
	//transform->position = Camera::GetPosition();
}
