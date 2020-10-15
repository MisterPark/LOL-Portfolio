#pragma once
#include "GameObject.h"

namespace PKH {
	class Effect4 :
		public GameObject
	{
	public:
		Effect4();
		~Effect4();
		void Ready();
		virtual void Update() override;
		void SetCode(int _Code) { EffectCode = _Code; }
	public:
		Vector3 dir;
		float Frame;
		int EffectCode;
	};
}

