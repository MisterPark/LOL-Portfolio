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
		static void GetViewMatrix(Matrix* outView);


	public:
		Vector3 look = Vector3(0, 0, 1);
		Vector3 up = Vector3(0, 1, 0);
		Vector3 right = Vector3(1, 0, 0);
	};
}


