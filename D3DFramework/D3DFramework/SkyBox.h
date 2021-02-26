#pragma once
#include "GameObject.h"

namespace Engine
{
	class SkyBox : public GameObject
	{
	private:
		SkyBox();
		virtual ~SkyBox();
	public:
		static SkyBox* GetInstance();
		static void Destroy();

		static void Show();
		static void Hide();

		static void SetTexture(TextureID upTexture);

		virtual void Update() override;
		virtual void Initialize() override;
		virtual void Release() override;
	};
}