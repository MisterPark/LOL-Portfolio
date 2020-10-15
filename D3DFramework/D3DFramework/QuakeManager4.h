#pragma once

namespace PKH {
	class QuakeManager4
	{
	private:
		QuakeManager4();
		~QuakeManager4();
	public:
		static QuakeManager4* GetInstance();
		static void Destroy();
		static void SetQuakeStart() { if (pInstance->QuakeStart == 0) pInstance->QuakeStart = 1; }
		static void Update();
		static void ObjPosSetQuake();
	public:
		static PKH::QuakeManager4* pInstance;
		float QuakePos;
		int QuakeStart;
	};
}
