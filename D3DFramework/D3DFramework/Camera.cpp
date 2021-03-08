#include "stdafx.h"
#include "Camera.h"

using namespace Engine;

Engine::Camera* Engine::Camera::main = nullptr;
map<wstring, Camera*> Camera::cams;

Engine::Camera::Camera()
{
	screenW = MainGame::GetWidth();
	screenH = MainGame::GetHeight();
	fovY = D3DXToRadian(60.f);

	this->transform->position = { 0,0,-3 };
	Matrix view;
	D3DXMatrixLookAtLH(&view, &transform->position, &transform->look, &transform->up);

	RenderManager::SetTransform(D3DTS_VIEW, &view);
	// 투영
	Matrix proj;
	D3DXMatrixPerspectiveFovLH(&proj, fovY,
		(float)screenW / screenH,
		nearClipPlane,
		farClipPlane);

	RenderManager::SetTransform(D3DTS_PROJECTION, &proj);
	isProjection3D = true;
}

Engine::Camera::~Camera()
{

}

Engine::Camera* Engine::Camera::GetInstance()
{
	if (main == nullptr)
	{
		main = new Engine::Camera;
		cams[L"MainCamera"] = main;
	}
	return main;
}

void Engine::Camera::Destroy()
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

void Engine::Camera::Update()
{
	float dt = Time::DeltaTime();
	
	if (Input::GetKey(VK_UP))
	{
		//offset.y += 10.f * dt;
	}
	if (Input::GetKey(VK_DOWN))
	{
		//offset.y -= 10.f * dt;
	}
	if (Input::GetKey(VK_NUMPAD7))
	{
		//transform->position.y += 100.f * dt;
		topViewPos.y += 10.f * dt;
	}
	if (Input::GetKey(VK_NUMPAD9))
	{
		//transform->position.y -= 100.f * dt;
		topViewPos.y -= 10.f * dt;
	}
	if (Input::GetKey(VK_NUMPAD8)) // 위
	{
		topViewPos.z += 10.f * dt;
		topViewLook.z += 10.f * dt;
	}
	if (Input::GetKey(VK_NUMPAD5)) // 아래
	{
		topViewPos.z -= 10.f * dt;
		topViewLook.z -= 10.f * dt;
	}
	if (Input::GetKey(VK_NUMPAD4)) // 왼
	{
		topViewPos.x -= 10.f * dt;
		topViewLook.x -= 10.f * dt;
	}
	if (Input::GetKey(VK_NUMPAD6)) // 오른
	{
		topViewPos.x += 10.f * dt;
		topViewLook.x += 10.f * dt;
	}
	if (Input::GetKeyDown('U'))
	{
		printf("look :%d,%d,%d\n", (int)transform->look.x, (int)transform->look.y, (int)transform->look.z);
		printf("pos :%d,%d,%d\n", (int)transform->position.x, (int)transform->position.y, (int)transform->position.z);
		topViewFlag = !topViewFlag;
	}

	if (Input::GetMouseWheelUp())
	{
		if (target != nullptr)
		{
			Vector3 direction = transform->look - transform->position;
			Vector3::Normalize(&direction);
			offset += direction * zoomSpeed;// *dt;
			
		}
	}
	else if (Input::GetMouseWheelDown())
	{
		if (target != nullptr)
		{
			Vector3 direction = transform->look - transform->position;
			Vector3::Normalize(&direction);
			offset -= direction * zoomSpeed;// *dt;
		}
	}
	
	// 포즈, 룩 세팅
	if (topViewFlag)
	{
		transform->look = topViewLook;
		transform->position = topViewPos;
	}
	else
	{
		if (nullptr != target)
		{
			transform->position = target->transform->position;
			transform->position += offset;

			transform->look = target->GetTransform()->position;
		}
	}

	// 뷰
	viewMatrix = Matrix::LookAtLH(transform->position, transform->look, transform->up);
	RenderManager::SetTransform(D3DTS_VIEW, &viewMatrix);

	// 투영
	
	PerspectiveProjection();
	OrthogonalProjection();

	if (isProjection3D)
	{
		projectionMatrix = perspectiveMatrix;
	}
	else
	{
		projectionMatrix = orthogonalMatrix;
	}

	RenderManager::SetTransform(D3DTS_PROJECTION, &projectionMatrix);
}



void Engine::Camera::Initialize()
{
}

void Engine::Camera::Release()
{
}

Vector3 Engine::Camera::GetPosition()
{
	return transform->position;
}

float Engine::Camera::GetX()
{
	return transform->position.x;
}

float Engine::Camera::GetY()
{
	return transform->position.y;
}

Matrix Engine::Camera::GetViewMatrix()
{
	return viewMatrix;
}

Matrix Engine::Camera::GetProjectionMatrix()
{
	return projectionMatrix;
}

Matrix Engine::Camera::GetPerspectiveMatrix()
{
	return perspectiveMatrix;
}

Matrix Engine::Camera::GetOrthogonalMatrix()
{
	return orthogonalMatrix;
}

void Engine::Camera::SetProjection3D(bool ProjectionSet)
{
	isProjection3D = ProjectionSet;
}

bool Engine::Camera::GetProjection3D()
{
	return isProjection3D;
}

Vector3 Engine::Camera::ScreenToWorldPoint(const Vector3& position, float zPos)
{
	Matrix viewProj = viewMatrix * projectionMatrix;
	
	// Screen To Projection
	Vector3 pos;
	pos.x = (position.x * 2.f / screenW) - 1.f;
	pos.y = -(position.y * 2.f / screenH) + 1.f;
	pos.z = zPos;

	// Projection To World
	Matrix inverseMat = Matrix::Inverse(viewProj);
	D3DXVec3TransformCoord(&pos, &pos, &inverseMat);
	return pos;
}

Vector3 Engine::Camera::WorldToScreenPoint(const Vector3& position)
{
	Matrix viewProj = viewMatrix * projectionMatrix;

	Vector3 pos; 
	D3DXVec3TransformCoord(&pos, &position, &viewProj);

	pos.x = (pos.x + 1.f) * 0.5f * screenW;
	pos.y = (pos.y - 1.f) * -0.5f * screenH;

	return pos;
}

Vector3 Engine::Camera::ScreenToWorldPointOrtho(const Vector3& position, float zPos)
{
	Matrix viewProj = viewMatrix * orthogonalMatrix;

	// Screen To Projection
	Vector3 pos;
	pos.x = (position.x * 2.f / screenW) - 1.f;
	pos.y = -(position.y * 2.f / screenH) + 1.f;
	pos.z = zPos;

	// Projection To World
	Matrix inverseMat = Matrix::Inverse(viewProj);
	D3DXVec3TransformCoord(&pos, &pos, &inverseMat);
	return pos;
}

Vector3 Engine::Camera::WorldToScreenPointOrtho(const Vector3& position)
{
	Matrix viewProj = viewMatrix * orthogonalMatrix;

	Vector3 pos;
	D3DXVec3TransformCoord(&pos, &position, &viewProj);

	pos.x = (pos.x + 1.f) * 0.5f * screenW;
	pos.y = (pos.y - 1.f) * -0.5f * screenH;

	return pos;
}

Ray Engine::Camera::ScreenPointToRay(Vector3 pos)
{
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

void Engine::Camera::SetTarget(GameObject* _target)
{
	target = _target;
	if (target != nullptr)
	{
		transform->position = target->transform->position;
		transform->position.y += 6.f;
		transform->position.z += 3.f;
	}
}

void Engine::Camera::SlowChaseTarget(GameObject * tar)
{
	isSlowChase = true;
	target = tar;
	slowTime = 0.f;
}

void Engine::Camera::Shake(float _duration, float _magnitude)
{
	isShake = true;
	shakeDuration = _duration;
	shakeMagnitude = _magnitude;
	originCamPos = transform->position;
}

void Engine::Camera::UpdateShake()
{
	if (isShake)
	{
		shakeDuration -= Time::DeltaTime();

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

void Engine::Camera::SetShakeDuration(float _duration)
{
	shakeDuration = _duration;
}

float Engine::Camera::GetFarPlane()
{
	return farClipPlane;
}

void Engine::Camera::PerspectiveProjection()
{
	perspectiveMatrix = Matrix::PerspectiveFovLH(fovY,
		(float)screenW / screenH,
		nearClipPlane,
		farClipPlane);
	//D3DXMatrixPerspectiveFovLH(&projectionMatrix, D3DX_PI * 0.5f,
	//	(float)dfCLIENT_WIDTH / dfCLIENT_HEIGHT,
	//	nearClipPlane,
	//	farClipPlane);
	
	
}

void Engine::Camera::OrthogonalProjection() 
{

	//D3DXMatrixOrthoLH(&proj, (float)7.6f, (float)5.7f, 0.0f, 10.f);
	//D3DXMatrixOrthoLH(&orthogonalMatrix, (float)screenW * 0.01f - screenW * 0.0005f,
	//	(float)screenH * 0.01f - screenH * 0.0005f, 0.0f, 10.f);
	D3DXMatrixOrthoLH(&orthogonalMatrix, (float)screenW,
		(float)screenH, nearClipPlane, farClipPlane);
	RenderManager::SetTransform(D3DTS_PROJECTION, &projectionMatrix);
}

Camera* Engine::Camera::CreateCamera(wstring id)
{
	auto find = cams.find(id);
	if (find != cams.end()) return find->second; // 이미 존재하면 리턴
	
	Camera* cam = new Camera();
	cams[id] = cam;
	return cam;
}

void Engine::Camera::DeleteCamera(wstring id)
{
	auto find = cams.find(id);
	if (find == cams.end()) return;

	Camera* cam = find->second;
	cams.erase(id);
	delete cam;

}

