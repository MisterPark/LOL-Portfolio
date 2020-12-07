#include "stdafx.h"
#include "Camera.h"

using namespace PKH;

PKH::Camera* PKH::Camera::main = nullptr;
map<wstring, Camera*> Camera::cams;

PKH::Camera::Camera()
{
	screenW = MainGame::GetWidth();
	screenH = MainGame::GetHeight();

	this->transform->position = { 0,0,-3 };
	Matrix view;
	D3DXMatrixLookAtLH(&view, &transform->position, &transform->look, &transform->up);

	RenderManager::SetTransform(D3DTS_VIEW, &view);
	// 투영
	Matrix proj;
	D3DXMatrixPerspectiveFovLH(&proj, D3DX_PI * 0.5f,
		(float)screenW / screenH,
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
	if (main == nullptr)
	{
		main = new PKH::Camera;
		cams[L"MainCamera"] = main;
	}
	return main;
}

void PKH::Camera::Destroy()
{
	if (main)
	{
		cams.erase(L"MainCamera");
		delete main;
		main = nullptr;
	}
	
	for (auto iter : cams)
	{
		delete iter.second;
	}

	cams.clear();
}

void PKH::Camera::Update()
{
	if (nullptr != target)
	{
		transform->position = target->transform->position;
		transform->position += offset;

		transform->look = target->GetTransform()->position;
	}

	if (InputManager::GetKey(VK_UP))
	{
		transform->position.y += 100.f * TimeManager::DeltaTime();
	}
	if (InputManager::GetKey(VK_DOWN))
	{
		transform->position.y -= 100.f * TimeManager::DeltaTime();
	}
	if (InputManager::GetMouseWheelUp())
	{
		if (target != nullptr)
		{
			Vector3 direction = transform->look - transform->position;
			Vector3::Normalize(&direction);
			offset += direction * zoomSpeed;// *TimeManager::DeltaTime();
			
		}
	}
	else if (InputManager::GetMouseWheelDown())
	{
		if (target != nullptr)
		{
			Vector3 direction = transform->look - transform->position;
			Vector3::Normalize(&direction);
			offset -= direction * zoomSpeed;// *TimeManager::DeltaTime();
		}
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

void PKH::Camera::Initialize()
{
}

void PKH::Camera::Release()
{
}

Vector3 PKH::Camera::GetPosition()
{
	return transform->position;
}

float PKH::Camera::GetX()
{
	return transform->position.x;
}

float PKH::Camera::GetY()
{
	return transform->position.y;
}

Matrix PKH::Camera::GetViewMatrix()
{
	return viewMatrix;
}

Matrix PKH::Camera::GetProjectionMatrix()
{
	return projectionMatrix;
}

void PKH::Camera::SetProjection3D(bool ProjectionSet)
{
	isProjection3D = ProjectionSet;
}

bool PKH::Camera::GetProjection3D()
{
	return isProjection3D;
}

Vector3 PKH::Camera::ScreenToWorldPoint(const Vector3& position, float zPos)
{
	Matrix viewProj = viewMatrix * projectionMatrix;
	
	// Screen To Projection
	Vector3 pos;
	pos.x = (position.x * 2.f / screenW) - 1.f;
	pos.y = -(position.y * 2.f / screenH) + 1.f;
	if(1.f == zPos) pos.z =  nearClipPlane;
	else pos.z = zPos;

	// Projection To World
	Matrix inverseMat = Matrix::Inverse(viewProj);
	D3DXVec3TransformCoord(&pos, &pos, &inverseMat);
	return pos;
}

Vector3 PKH::Camera::WorldToScreenPoint(const Vector3& position)
{
	Matrix viewProj = viewMatrix * projectionMatrix;

	Vector3 pos; 
	D3DXVec3TransformCoord(&pos, &position, &viewProj);

	pos.x = (pos.x + 1.f) * 0.5f * screenW;
	pos.y = (pos.y - 1.f) * -0.5f * screenH;

	return pos;
}

Ray PKH::Camera::ScreenPointToRay(Vector3 pos)
{
	// TODO : 이거 정상작동 안할지도 모름 테스트해봐야함
	// 비정상일시 : ScreenToWorld 에서 포지션 가져온 뒤
	// 포지션 - 카메라 포지션 = 방향.노말라이즈 이렇게 바꾸셈

	Ray ray;
	ray.origin = transform->position;

	Matrix viewProj = viewMatrix * projectionMatrix;

	// Screen To Projection
	Vector3 direction;
	direction.x = (pos.x * 2.f / screenW) - 1.f;
	direction.y = -(pos.y * 2.f / screenH) + 1.f;
	direction.z = nearClipPlane;

	// Projection To World
	Matrix inverseMat = Matrix::Inverse(viewProj);
	D3DXVec3TransformCoord(&direction, &direction, &inverseMat);

	direction = direction - ray.origin;
	Vector3::Normalize(&direction);

	ray.direction = direction;


	return ray;
}

void PKH::Camera::SetTarget(GameObject* _target)
{
	target = _target;
	if (target != nullptr)
	{
		transform->position = target->transform->position;
		transform->position.y += 6.f;
		transform->position.z += 3.f;
	}
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
	shakeDuration = _duration;
}

void PKH::Camera::PerspectiveProjection()
{
	projectionMatrix = Matrix::PerspectiveFovLH(D3DXToRadian(90.f),
		(float)screenW / screenH,
		nearClipPlane,
		farClipPlane);
	//D3DXMatrixPerspectiveFovLH(&projectionMatrix, D3DX_PI * 0.5f,
	//	(float)dfCLIENT_WIDTH / dfCLIENT_HEIGHT,
	//	nearClipPlane,
	//	farClipPlane);
	RenderManager::SetTransform(D3DTS_PROJECTION, &projectionMatrix);
}

void PKH::Camera::OrthogonalProjection() 
{

	//D3DXMatrixOrthoLH(&proj, (float)7.6f, (float)5.7f, 0.0f, 10.f);
	D3DXMatrixOrthoLH(&projectionMatrix, (float)screenW * 0.01f - screenW * 0.0005f,
		(float)screenH * 0.01f - screenH * 0.0005f, 0.0f, 10.f);
	RenderManager::SetTransform(D3DTS_PROJECTION, &projectionMatrix);
}

Camera* PKH::Camera::CreateCamera(wstring key)
{
	auto find = cams.find(key);
	if (find != cams.end()) return find->second; // 이미 존재하면 리턴
	
	Camera* cam = new Camera();
	cams[key] = cam;
	return cam;
}

void PKH::Camera::DeleteCamera(wstring key)
{
	auto find = cams.find(key);
	if (find == cams.end()) return;

	Camera* cam = find->second;
	cams.erase(key);
	delete cam;

}

