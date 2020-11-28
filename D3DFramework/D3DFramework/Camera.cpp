#include "stdafx.h"
#include "Camera.h"

using namespace PKH;

PKH::Camera* pCamera = nullptr;


PKH::Camera::Camera()
{
	
	this->transform->position = { 0,0,-3 };
	Matrix view;
	//GetViewMatrix(&view);
	D3DXMatrixLookAtLH(&view, &transform->position, &transform->look, &transform->up);


	RenderManager::SetTransform(D3DTS_VIEW, &view);

	// 투영
	Matrix proj;
	D3DXMatrixPerspectiveFovLH(&proj, D3DX_PI * 0.5f,
		(float)dfCLIENT_WIDTH / dfCLIENT_HEIGHT,
		nearClipPlane,
		farClipPlane);

	RenderManager::SetTransform(D3DTS_PROJECTION, &proj);
	isProjection3D = true;
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
	if (InputManager::GetKey(VK_UP))
	{
		transform->position.y += 10.f * TimeManager::DeltaTime();
	}
	if (InputManager::GetKey(VK_DOWN))
	{
		transform->position.y -= 10.f * TimeManager::DeltaTime();
	}
	if (nullptr != target)
	{
		transform->position = target->GetTransform()->position - (target->GetTransform()->look * target->GetTransform()->scale.y * 6.f);
		//transform->position.y += 1.f;
		transform->position.y += target->GetTransform()->scale.y * 5.f;

		transform->look = target->GetTransform()->position + (target->GetTransform()->look * 10.f);
	}

	viewMatrix = Matrix::LookAtLH(transform->position, transform->look, transform->up);
	RenderManager::SetTransform(D3DTS_VIEW, &viewMatrix);

	// 투영
	if (isProjection3D)
		PerspectiveProjection();
	else
		OrthogonalProjection();
}

void PKH::Camera::Render()
{
}

Vector3 PKH::Camera::GetPosition()
{
	return pCamera->transform->position;
}

float PKH::Camera::GetX()
{
	return pCamera->transform->position.x;
}

float PKH::Camera::GetY()
{
	return pCamera->transform->position.y;
}

Matrix PKH::Camera::GetViewMatrix()
{
	return pCamera->viewMatrix;
}

Matrix PKH::Camera::GetProjectionMatrix()
{
	return pCamera->projectionMatrix;
}

void PKH::Camera::SetProjection3D(bool ProjectionSet)
{
	pCamera->isProjection3D = ProjectionSet;
}

bool PKH::Camera::GetProjection3D()
{
	return pCamera->isProjection3D;
}

Vector3 PKH::Camera::ScreenToWorldPoint(const Vector3& position, float zPos)
{
	Matrix viewProj = pCamera->viewMatrix * pCamera->projectionMatrix;
	
	// Screen To Projection
	Vector3 pos;
	pos.x = (position.x * 2.f / dfCLIENT_WIDTH) - 1.f;
	pos.y = -(position.y * 2.f / dfCLIENT_HEIGHT) + 1.f;
	if(1.f == zPos) pos.z =  pCamera->nearClipPlane;
	else pos.z = zPos;

	// Projection To World
	Matrix inverseMat = Matrix::Inverse(viewProj);
	D3DXVec3TransformCoord(&pos, &pos, &inverseMat);
	return pos;
}

Vector3 PKH::Camera::WorldToScreenPoint(const Vector3& position)
{
	Matrix viewProj = pCamera->viewMatrix * pCamera->projectionMatrix;

	Vector3 pos; 
	D3DXVec3TransformCoord(&pos, &position, &viewProj);

	pos.x = (pos.x + 1.f) * 0.5f * dfCLIENT_WIDTH;
	pos.y = (pos.y - 1.f) * -0.5f * dfCLIENT_HEIGHT;

	return pos;
}

Ray PKH::Camera::ScreenPointToRay(Vector3 pos)
{
	// TODO : 이거 정상작동 안할지도 모름 테스트해봐야함
	// 비정상일시 : ScreenToWorld 에서 포지션 가져온 뒤
	// 포지션 - 카메라 포지션 = 방향.노말라이즈 이렇게 바꾸셈

	Ray ray;
	ray.origin = pCamera->transform->position;

	Matrix viewProj = pCamera->viewMatrix * pCamera->projectionMatrix;

	// Screen To Projection
	Vector3 direction;
	direction.x = (pos.x * 2.f / dfCLIENT_WIDTH) - 1.f;
	direction.y = -(pos.y * 2.f / dfCLIENT_HEIGHT) + 1.f;
	direction.z = pCamera->nearClipPlane;

	// Projection To World
	Matrix inverseMat = Matrix::Inverse(viewProj);
	D3DXVec3TransformCoord(&direction, &direction, &inverseMat);

	direction = direction - ray.origin;
	Vector3::Normalize(&direction);

	ray.direction = direction;


	return ray;
}

void PKH::Camera::SlowChaseTarget(GameObject * tar)
{
	isSlowChase = true;
	target = tar;
	slowTime = 0.f;
}

void PKH::Camera::Shake(float _duration, float _magnitude)
{
	isShake = true;
	shakeDuration = _duration;
	shakeMagnitude = _magnitude;
	originCamPos = transform->position;
}

void PKH::Camera::UpdateShake()
{
	if (isShake)
	{
		shakeDuration -= TimeManager::DeltaTime();

		if (0 >= shakeDuration)
		{
			isShake = false;
			transform->position = originCamPos;
			shakeDuration = 0.f;
			return;
		}

		float ranX = Random::Range(-1.f, 1.f);
		float ranY = Random::Range(-1.f, 1.f);
		float ranZ = Random::Range(-1.f, 1.f);

		Vector3 randVec = { ranX, ranY, ranZ };

		if (nullptr == target)
			transform->position = originCamPos + (randVec * shakeMagnitude);
		else
			transform->position = transform->position + (randVec * shakeMagnitude);
	}
}

void PKH::Camera::SetShakeDuration(float _duration)
{
	pCamera->shakeDuration = _duration;
}

void PKH::Camera::PerspectiveProjection()
{
	pCamera->projectionMatrix = Matrix::PerspectiveFovLH(D3DXToRadian(90.f),
		(float)dfCLIENT_WIDTH / dfCLIENT_HEIGHT,
		nearClipPlane,
		farClipPlane);
	//D3DXMatrixPerspectiveFovLH(&pCamera->projectionMatrix, D3DX_PI * 0.5f,
	//	(float)dfCLIENT_WIDTH / dfCLIENT_HEIGHT,
	//	nearClipPlane,
	//	farClipPlane);
	RenderManager::SetTransform(D3DTS_PROJECTION, &pCamera->projectionMatrix);
}

void PKH::Camera::OrthogonalProjection() 
{

	//D3DXMatrixOrthoLH(&proj, (float)7.6f, (float)5.7f, 0.0f, 10.f);
	D3DXMatrixOrthoLH(&pCamera->projectionMatrix, (float)dfCLIENT_WIDTH * 0.01f - dfCLIENT_WIDTH * 0.0005f,
		(float)dfCLIENT_HEIGHT * 0.01f - dfCLIENT_HEIGHT * 0.0005f, 0.0f, 10.f);
	RenderManager::SetTransform(D3DTS_PROJECTION, &pCamera->projectionMatrix);
}

void PKH::Camera::Initialize()
{
}

void PKH::Camera::Release()
{
}
