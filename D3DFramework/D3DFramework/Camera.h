#pragma once
#include "GameObject.h"

namespace PKH
{
	class Camera : public GameObject
	{
	private:
		Camera();
		virtual ~Camera();
	public:
		static Camera* GetInstance();
		static void Destroy();
		// GameObject을(를) 통해 상속됨
		virtual void Update() override;
		virtual void Render() override;


		static Vector3 GetPosition();
		static float GetX();
		static float GetY();
		static Matrix GetViewMatrix();
		static Matrix GetProjectionMatrix();
		static void GetViewMatrix(Matrix* outView);
		static bool GetProjection3D();
		static void SetProjection3D(bool ProjectionSet);

		static Vector3 ScreenToWorldPoint(const Vector3& position);
		static Vector3 WorldToScreenPoint(const Vector3& position);

	private:
		void PerspectiveProjection();
		void OrthogonalProjection();
		


	private:
		float nearClipPlane = 1.f;
		float farClipPlane = 1000.f;
		bool isProjection3D;
		Matrix viewMatrix;
		Matrix projectionMatrix;
	};
}


