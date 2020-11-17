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
		virtual void Initialize() override;
		virtual void Release() override;

		static Vector3 GetPosition();
		static float GetX();
		static float GetY();
		static Matrix GetViewMatrix();
		static Matrix GetProjectionMatrix();
		static bool GetProjection3D();
		static void SetProjection3D(bool ProjectionSet);

		static Vector3 ScreenToWorldPoint(const Vector3& position, float zPos = 1.f);
		static Vector3 WorldToScreenPoint(const Vector3& position);

		void SetTarget(GameObject* tar) { target = tar; }
		void SlowChaseTarget(GameObject* tar);

		// 카메라 흔들기
		void Shake(float _duration = 0.05f, float _magnitude = 0.03f);
		void UpdateShake();
		static void SetShakeDuration(float _duration);

	private:
		void PerspectiveProjection();
		void OrthogonalProjection();

	private:
		float nearClipPlane = 1.f;
		float farClipPlane = 1000.f;
		bool isProjection3D;
		Matrix viewMatrix;
		Matrix projectionMatrix;
		GameObject* target = nullptr;

		// 카메라 천천히 따라가기
		bool isSlowChase = false;
		float slowTime = 0.f;

		// 카메라 흔들기
		bool isShake = false;
		float shakeDuration;
		float shakeMagnitude;
		Vector3 originCamPos;
	};
}