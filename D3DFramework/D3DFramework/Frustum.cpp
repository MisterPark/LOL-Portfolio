#include "stdafx.h"
#include "Frustum.h"

using namespace PKH;

Frustum* pFrustum = nullptr;

Frustum::Frustum()
{
	Initialize();
}

Frustum::~Frustum()
{
}

void Frustum::Initialize()
{
	point[0] = Vector3(-1.f, 1.f, 0.f);
	point[1] = Vector3(1.f, 1.f, 0.f);
	point[2] = Vector3(1.f, -1.f, 0.f);
	point[3] = Vector3(-1.f, -1.f, 0.f);

	point[4] = Vector3(-1.f, 1.f, 1.f);
	point[5] = Vector3(1.f, 1.f, 1.f);
	point[6] = Vector3(1.f, -1.f, 1.f);
	point[7] = Vector3(-1.f, -1.f, 1.f);
}

Frustum* PKH::Frustum::GetInstance()
{
	if (pFrustum == nullptr)
	{
		pFrustum = new Frustum();
	}
	return pFrustum;
}

void PKH::Frustum::Destroy()
{
	if (pFrustum)
	{
		delete pFrustum;
		pFrustum = nullptr;
	}
}

void PKH::Frustum::Update()
{
	pFrustum->Initialize();

	Matrix matProj = Camera::main->GetProjectionMatrix();
	Matrix matView = Camera::main->GetViewMatrix();

	matProj = Matrix::Inverse(matProj);
	matView = Matrix::Inverse(matView);

	for (int i = 0; i < 8; i++)
	{
		D3DXVec3TransformCoord(&pFrustum->point[i], &pFrustum->point[i], &matProj);
		D3DXVec3TransformCoord(&pFrustum->point[i], &pFrustum->point[i], &matView);
	}

	D3DXPlaneFromPoints(&pFrustum->plane[0], &pFrustum->point[1], &pFrustum->point[5], &pFrustum->point[6]);

	//x-
	D3DXPlaneFromPoints(&pFrustum->plane[1], &pFrustum->point[4], &pFrustum->point[0], &pFrustum->point[3]);

	//y+
	D3DXPlaneFromPoints(&pFrustum->plane[2], &pFrustum->point[4], &pFrustum->point[5], &pFrustum->point[1]);

	//y-
	D3DXPlaneFromPoints(&pFrustum->plane[3], &pFrustum->point[3], &pFrustum->point[2], &pFrustum->point[6]);

	//z+
	D3DXPlaneFromPoints(&pFrustum->plane[4], &pFrustum->point[7], &pFrustum->point[6], &pFrustum->point[5]);

	//z-
	D3DXPlaneFromPoints(&pFrustum->plane[5], &pFrustum->point[0], &pFrustum->point[1], &pFrustum->point[2]);


}

bool PKH::Frustum::Intersect(const Vector3* pWorldPos)
{
	float result = 0.f;

	for (int i = 0; i < 6; i++)
	{
		result = D3DXPlaneDotCoord(&pFrustum->plane[i], pWorldPos);

		if (result > 0.f)
		{
			return false;
		}
	}

	return true;
}

bool Frustum::Intersect(const Vector3* pWorldPos, const float& radius)
{
	float result = 0.f;

	for (int i = 0; i < 6; i++)
	{
		result = D3DXPlaneDotCoord(&pFrustum->plane[i], pWorldPos);

		if (result > radius)
		{
			return false;
		}
	}

	return true;
}
