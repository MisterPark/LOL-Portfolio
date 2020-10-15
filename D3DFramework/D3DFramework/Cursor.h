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
		static void Hide();




		// GameObject을(를) 통해 상속됨
		virtual void Update() override;
		virtual void Render() override;

	private:
		bool isShow = true;
	};
}


