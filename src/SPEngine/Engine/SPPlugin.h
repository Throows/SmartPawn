#pragma once

#include "Core.h"

namespace SP
{

	class SP_API SPPlugin
	{
	public:
		SPPlugin();
		~SPPlugin() = default;

		void SetAction();
		int GetInfo();
	};
};