#pragma once
#include "GameObject.h"

namespace PKH
{
	class CubeMan :
		public GameObject
	{
	public:

		CubeMan();
		virtual ~CubeMan();

		virtual void Update() override;
	};

}

