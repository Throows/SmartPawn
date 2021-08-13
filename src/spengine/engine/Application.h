#pragma once

#include "SPpch.h"

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