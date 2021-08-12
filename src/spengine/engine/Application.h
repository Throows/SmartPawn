#pragma once

#include "SPpch.h"
#include "Core.h"

namespace SP {

	class Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
	private:
	};

	Application* CreateApplication();
}