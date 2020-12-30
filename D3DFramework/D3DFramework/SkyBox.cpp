#include "stdafx.h"
#include "SkyBox.h"
#include "Rectangle.h"

SkyBox* pSkyBox = nullptr;

PKH::SkyBox::SkyBox()
{
	isVisible = false;
	transform->scale = { 3,3,3 };
	transform->position = { 0,0,0 };

	CustomMesh* mesh = (CustomMesh*)AddComponent<PKH::Rectangle>(L"F");
	mesh->SetBlendMode(BlendMode::ALPHA_TEST);
	mesh->SetZReadMode(ZReadMode::OFF);
	mesh->SetZWriteMode(ZWriteMode::OFF);

//	mesh->SetTexture(TextureKey::SKY_F);
	mesh->SetVertexPos(0, Vector3(-1.0f, -1.0f, 1.0f));
	mesh->SetVertexPos(1, Vector3(-1.0f, 1.0f, 1.0f));
	mesh->SetVertexPos(2, Vector3(1.0f, 1.0f, 1.0f));
	mesh->SetVertexPos(3, Vector3(1.0f, -1.0f, 1.0f));
	
	mesh = (CustomMesh*)AddComponent<PKH::Rectangle>(L"B");
	mesh->SetBlendMode(BlendMode::ALPHA_TEST);
	mesh->SetZReadMode(ZReadMode::OFF);
	mesh->SetZWriteMode(ZWriteMode::OFF);

	//mesh->SetTexture(TextureKey::SKY_B);
	mesh->SetVertexPos(0, Vector3(1.0f, -1.0f, -1.0f));
	mesh->SetVertexPos(1, Vector3(1.0f, 1.0f, -1.0f));
	mesh->SetVertexPos(2, Vector3(-1.0f, 1.0f, -1.0f));
	mesh->SetVertexPos(3, Vector3(-1.0f, -1.0f, -1.0f));

	mesh = (CustomMesh*)AddComponent<PKH::Rectangle>(L"L");
	mesh->SetBlendMode(BlendMode::ALPHA_TEST);
	mesh->SetZReadMode(ZReadMode::OFF);
	mesh->SetZWriteMode(ZWriteMode::OFF);

	//mesh->SetTexture(TextureKey::SKY_L);
	mesh->SetVertexPos(0, Vector3(-1.0f, -1.0f, -1.0f));
	mesh->SetVertexPos(1, Vector3(-1.0f, 1.0f, -1.0f));
	mesh->SetVertexPos(2, Vector3(-1.0f, 1.0f, 1.0f));
	mesh->SetVertexPos(3, Vector3(-1.0f, -1.0f, 1.0f));

	mesh = (CustomMesh*)AddComponent<PKH::Rectangle>(L"R");
	mesh->SetBlendMode(BlendMode::ALPHA_TEST);
	mesh->SetZReadMode(ZReadMode::OFF);
	mesh->SetZWriteMode(ZWriteMode::OFF);

	//mesh->SetTexture(TextureKey::SKY_R);
	mesh->SetVertexPos(0, Vector3(1.0f, -1.0f, 1.0f));
	mesh->SetVertexPos(1, Vector3(1.0f, 1.0f, 1.0f));
	mesh->SetVertexPos(2, Vector3(1.0f, 1.0f, -1.0f));
	mesh->SetVertexPos(3, Vector3(1.0f, -1.0f, -1.0f));

	mesh = (CustomMesh*)AddComponent<PKH::Rectangle>(L"U");
	mesh->SetBlendMode(BlendMode::ALPHA_TEST);
	mesh->SetZReadMode(ZReadMode::OFF);
	mesh->SetZWriteMode(ZWriteMode::OFF);

	//mesh->SetTexture(TextureKey::SKY_U);
	mesh->SetVertexPos(0, Vector3(-1.0f, 1.0f, 1.0f));
	mesh->SetVertexPos(1, Vector3(-1.0f, 1.0f, -1.0f));
	mesh->SetVertexPos(2, Vector3(1.0f, 1.0f, -1.0f));
	mesh->SetVertexPos(3, Vector3(1.0f, 1.0f, 1.0f));

	mesh = (CustomMesh*)AddComponent<PKH::Rectangle>(L"D");
	mesh->SetBlendMode(BlendMode::ALPHA_TEST);
	mesh->SetZReadMode(ZReadMode::OFF);
	mesh->SetZWriteMode(ZWriteMode::OFF);

	//mesh->SetTexture(TextureKey::SKY_D);
	mesh->SetVertexPos(0, Vector3(-1.0f, -1.0f, -1.0f));
	mesh->SetVertexPos(1, Vector3(-1.0f, -1.0f, 1.0f));
	mesh->SetVertexPos(2, Vector3(1.0f, -1.0f, 1.0f));
	mesh->SetVertexPos(3, Vector3(1.0f, -1.0f, -1.0f));

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

void PKH::SkyBox::SetTexture(TextureID upTexture)
{
	int id = (int)upTexture;
	//CustomMesh* mesh = (CustomMesh*)pSkyBox->GetComponent(L"U");
	//mesh->SetTexture((TextureID)id);
	//id++;
	//mesh = (CustomMesh*)pSkyBox->GetComponent(L"D");
	//mesh->SetTexture((TextureID)id);
	//id++;
	//mesh = (CustomMesh*)pSkyBox->GetComponent(L"L");
	//mesh->SetTexture((TextureID)id);
	//id++;
	//mesh = (CustomMesh*)pSkyBox->GetComponent(L"R");
	//mesh->SetTexture((TextureID)id);
	//id++;
	//mesh = (CustomMesh*)pSkyBox->GetComponent(L"F");
	//mesh->SetTexture((TextureID)id);
	//id++;
	//mesh = (CustomMesh*)pSkyBox->GetComponent(L"B");
	//mesh->SetTexture((TextureID)id);
}

void PKH::SkyBox::Update()
{

	transform->position = Camera::GetInstance()->transform->position;

	GameObject::Update();
}

void PKH::SkyBox::Initialize()
{
}

void PKH::SkyBox::Release()
{
}
