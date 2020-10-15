#pragma once
#include "GameObject.h"

namespace PKH
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

		virtual void Update() override;

	public:
	};
}


