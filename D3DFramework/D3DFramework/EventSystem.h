#pragma once

namespace Engine
{
	class MouseEventArg : public EventArgs
	{
	public:

	};

	class EventSystem
	{
	private:
		EventSystem();
		~EventSystem();

	public:
		static EventSystem* GetInstance();
		static void Destroy();

		static void Clear();
		static void Update();


		static bool IsPointerOverGameObject();

	private:
		static void CheckPointerOverGameObject();

	private:
		static bool isPointerOverGameObject;
	};


}
