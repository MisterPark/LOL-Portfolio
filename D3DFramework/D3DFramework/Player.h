#pragma once
#include "GameObject.h"

namespace PKH
{
	class Player :
		public GameObject
	{
	public:
		Player();
		virtual ~Player();

		virtual void Update() override;
		virtual void Render() override;

	};


}
