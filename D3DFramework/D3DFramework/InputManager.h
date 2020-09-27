#pragma once

#define RANGE_OF_KEYS 256
#define dfINPUT_LIFE_FRAME 2

namespace PKH
{
	enum class Keys
	{
		LBUTTON,
		RBUTTON,
		RBUTTON_UP,
		LBUTTON_UP,
		LBUTTON_DOWN,
		RBUTTON_DOWN,
		LBUTTON_DOUBLE,
		RBUTTON_DOUBLE,

		END
	};

	class InputManager
	{
	private:
		InputManager();
		~InputManager();

	public:
		static InputManager* GetInstance();
		static void Update();
		static void Initialize();
		static void Destroy();
		static void Clear();
		static void ClearMouseState();

		// 키 프레스
		static bool GetKey(int _vkey);
		// 키 다운
		static bool GetKeyDown(int _vkey);
		// 키 업
		static bool GetKeyUp(int _vkey);


		static bool GetMouseLButton();
		static bool GetMouseLButtonUp();
		static bool GetMouseLButtonDown();
		static bool GetMouseLButtonDouble();

		static bool GetMouseRButton();
		static bool GetMouseRButtonUp();
		static bool GetMouseRButtonDown();
		static bool GetMouseRButtonDouble();

		static POINT GetMousePosOnClient();
		static POINT GetMousePosOnWorld();


	private:
		bool keys[RANGE_OF_KEYS] = {};
		bool keyDowns[RANGE_OF_KEYS] = {};
		bool keyUps[RANGE_OF_KEYS] = {};

	public:
		bool mouse[MaxOfEnum<Keys>()] = {};

	};


}
