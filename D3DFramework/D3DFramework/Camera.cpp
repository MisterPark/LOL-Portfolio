#include "stdafx.h"
#include "Camera.h"

using namespace PKH;

PKH::Camera* pCamera = nullptr;


PKH::Camera::Camera()
{
	// ºä


	
}

PKH::Camera::~Camera()
{
}

PKH::Camera* PKH::Camera::GetInstance()
{
	if (pCamera == nullptr)
	{
		pCamera = new PKH::Camera;
	}
	return pCamera;
}

void PKH::Camera::Destroy()
{
	if (pCamera)
	{
		delete pCamera;
		pCamera = nullptr;
	}
}

void PKH::Camera::Update()
{
	if (InputManager::GetKey('W'))
	{
		transform.position.y += 1.0f * TimeManager::DeltaTime();
	}
	if (InputManager::GetKey('A'))
	{
		transform.position.x -= 1.0f * TimeManager::DeltaTime();
	}
	if (InputManager::GetKey('S'))
	{
		transform.position.y -= 1.0f * TimeManager::DeltaTime();
	}
	if (InputManager::GetKey('D'))
	{
		transform.position.x += 1.0f * TimeManager::DeltaTime();
	}
	if (InputManager::GetKey('Q'))
	{
		transform.position.z += 1.0f * TimeManager::DeltaTime();
	}
	if (InputManager::GetKey('E'))
	{
		transform.position.z -= 1.0f * TimeManager::DeltaTime();
	}

	
	Matrix view;
	//GetViewMatrix(&view);
	Vector3 target = transform.position;
	target.z += 3;
	D3DXMatrixLookAtLH(&view, &transform.position, &target, &this->up);
	D2DRenderManager::GetDevice()->SetTransform(D3DTS_VIEW, &view);

	// Åõ¿µ
	Matrix proj;
	D3DXMatrixPerspectiveFovLH(&proj, D3DX_PI * 0.5f,
		(float)dfCLIENT_WIDTH / dfCLIENT_HEIGHT,
		1.0f,
		1000.f);

	D2DRenderManager::GetDevice()->SetTransform(D3DTS_PROJECTION, &proj);

}

void PKH::Camera::Render()
{
}

Vector3 PKH::Camera::GetPosition()
{
	return pCamera->transform.position;
}

float PKH::Camera::GetX()
{
	return pCamera->transform.position.x;
}

float PKH::Camera::GetY()
{
	return pCamera->transform.position.y;
}

void PKH::Camera::GetViewMatrix(Matrix* outView)
{
	// ·è º¤ÅÍ¸¦ ´ÜÀ§È­
	Vector3::Normalize(&pCamera->look);
	// ·èº¤ÅÍ¸¦ ±âÁØÀ¸·Î ¾÷º¤ÅÍ Á¶Á¤ (float ÀÇ ¿ÀÂ÷ Á¶Á¤)
	pCamera->up = Vector3::Cross(&pCamera->look ,&pCamera->right);
	Vector3::Normalize(&pCamera->up);
	// ·èº¤ÅÍ¸¦ ±âÁØÀ¸·Î ·ÖÀÌÆ®º¤ÅÍ Á¶Á¤ (float ÀÇ ¿ÀÂ÷ Á¶Á¤)
	pCamera->right = Vector3::Cross(&pCamera->up, &pCamera->look);
	Vector3::Normalize(&pCamera->right);

	if (outView == nullptr) return;

	outView->_11 = pCamera->right.x;
	outView->_12 = pCamera->up.x;
	outView->_13 = pCamera->look.x;
	outView->_14 = 0.f;

	outView->_21 = pCamera->right.y;
	outView->_22 = pCamera->up.y;
	outView->_23 = pCamera->look.y;
	outView->_24 = 0.f;

	outView->_31 = pCamera->right.z;
	outView->_32 = pCamera->right.z;
	outView->_33 = pCamera->right.z;
	outView->_34 = 0.f;

	outView->_41 = pCamera->transform.position.x;
	outView->_42 = pCamera->transform.position.y;
	outView->_43 = pCamera->transform.position.z;
	outView->_44 = 1.f;
}
