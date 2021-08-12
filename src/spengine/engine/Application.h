#pragma once

#include "SPpch.h"
#include "Core.h"

namespace SP {

	class SP_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
	private:
	};

	Application* CreateApplication();
}