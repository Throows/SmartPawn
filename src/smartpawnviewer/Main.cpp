#include "Core/Application.hpp"

#ifdef SP_PLATFORM_WIN
#include <Windows.h>
#elif SP_PLATFORM_DARWIN
#include <unistd.h>
#endif

#ifdef SP_PLATFORM_WIN

#ifdef WIN_START
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) 
#else
int main(int argc, char** argv)
#endif
{
	SP::Logger::Init();
	SPV_APP_INFO("Logger Initialized successfully !");
	SPV::Application app{};
	return app.Run();
}

#elif SP_PLATFORM_DARWIN

int main(int argc, char** argv) 
{
	(void)argc, (void)argv;
	SP::Logger::Init();
	SPV_APP_INFO("Logger Initialized successfully !");
	SPV::Application app{};
	return app.Run();
}

#endif