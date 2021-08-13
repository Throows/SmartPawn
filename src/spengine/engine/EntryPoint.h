#pragma once

#ifdef SP_PLATFORM_WIN
	
int main(int argc, char** argv) 
{
	SP::Logger::Init();
	SP_ENGINE_INFO("Hi from Engine !");
	auto app = SP::CreateApplication();
	app->Run();
	delete app;
}

#elif SP_PLATFORM_DARWIN
	int main(int argc, char** argv) {

		auto app = SP::CreateApplication();
		app->Run();
		delete app;
	}
#endif

