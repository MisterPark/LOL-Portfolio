#pragma once
#include "GameObject.h"

namespace PKH
{
	class Cursor : public GameObject
	{
	private:
		Cursor();
		~Cursor();
	public:
		static Cursor* GetInstance();
		static void Destroy();

		static Vector3 GetMousePos();
		static void Show();
		static void Show(bool on);
		static void Hide();


		virtual void Update() override;
		virtual void Render() override;
		virtual void Initialize() override;
		virtual void Release() override;

		static bool IsVisible();

	private:
		bool isVisible = true;

		
	};
}


