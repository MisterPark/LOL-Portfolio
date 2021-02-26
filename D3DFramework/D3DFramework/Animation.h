#pragma once
#include "IComponent.h"

namespace Engine
{

	class Animation :
		public IComponent
	{
	public:
		struct Node
		{
			UINT index = 0;
			string name;
			bool isLoop = false;
			float period = 0.f;
			float speed = 1.f;
		};

		explicit Animation(GameObject* owner);
		explicit Animation(const Animation& rhs);
		virtual ~Animation();

		virtual void PostUpdate();
		virtual IComponent* Clone() override;

	public:
		void AttachToDynamicMesh(DynamicMesh* dmesh);
		string GetNameByState(int _state);
		UINT GetIndexByState(int _state);
		UINT GetCurrentAnimation();

		void SetState(int _state);
		void SetLoop(int _state, bool loop);
		void SetSpeed(int _state, float speed);
		bool IsFrameEnd();

		void Stop();
		void Resume();

	private:
		int state = 0;
		DynamicMesh* dmesh = nullptr;
		
		UINT currentAnim = 0;
		bool stopFlag = false;
	public:
		map<UINT, Animation::Node> animsets;
	};
}


