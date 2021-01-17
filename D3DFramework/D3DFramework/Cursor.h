#pragma once
#include "GameObject.h"

namespace PKH
{
	enum class CursorMode { Normal, SingleTarget };

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
		static void SetTexture(const wstring& key);
		static void SetRenderCenter(bool isCenter);

		static void SetMode(CursorMode _mode);
		static void ChangeMode();

	private:
		wstring textureKey;
		bool isRenderCenter = false;
		CursorMode mode = CursorMode::Normal;
	};
}


