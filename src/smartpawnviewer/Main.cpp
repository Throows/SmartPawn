#include "Core/Application.hpp"

#ifdef SP_PLATFORM_WIN
#include <Windows.h>
#elif SP_PLATFORM_DARWIN
#include <unistd.h>
#endif

#if defined(SP_PLATFORM_WIN) && defined(WIN_START)

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) 
{
	(void)hInstance, (void)hPrevInstance, (void)lpCmdLine, (void)nCmdShow;
	SP::Logger::Init();
	SPV::Application app{};
	return app.Run();
}
#else

int main(int argc, char** argv)
{
	(void)argc, (void)argv;
#ifdef SP_PLATFORM_DARWIN
	std::filesystem::path exePath = argv[0];
	std::filesystem::current_path(exePath.parent_path());
#endif
	SP::Logger::Init();
	SPV::Application app{};
	return app.Run();
}
#endif