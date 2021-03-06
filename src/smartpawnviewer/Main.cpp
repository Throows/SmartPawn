#include <Core/pch.h>
#include "Core/Application.h"

#ifdef SP_PLATFORM_WIN
	
int main(int argc, char** argv) 
{
	SP::Logger::Init();
	SP_APP_INFO("Logger Initialized successfully !");
	auto app = new SP::Application();
	app->Run();
	delete app;
}

#elif SP_PLATFORM_DARWIN
	int main(int argc, char** argv) {

		SP::Logger::Init();
		auto app = new SP::Application();
		app->Run();
		delete app;
	}
#endif

