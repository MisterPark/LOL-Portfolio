#pragma once
#include "IComponent.h"

namespace Engine
{
	typedef UINT AnimationIndex;

	class Animation :
		public IComponent
	{
	public:
		struct Node
		{
			AnimationIndex index = 0;
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
		AnimationIndex GetIndexByState(int _state);
		AnimationIndex GetCurrentAnimation();
		int GetState();

		void SetState(int _state);
		void SetLoop(int _state, bool loop);
		void SetSpeed(int _state, float speed);
		bool IsFrameEnd();

		void Stop();
		void Resume();
		void Reset();

	private:
		int state = 0;
		DynamicMesh* dmesh = nullptr;
		
		AnimationIndex currentAnim = 0;
		bool stopFlag = false;
	public:
		map<UINT, Animation::Node> animsets;
	};
}


