#include <Core/pch.hpp>
#include "Core/Application.hpp"

#ifdef SP_PLATFORM_WIN
#include <Windows.h>
#elif SP_PLATFORM_DARWIN
#include <unistd.h>
#endif

#ifdef SP_PLATFORM_WIN

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) 
{
	SPV::Logger::Init();
	SP_APP_INFO("Logger Initialized successfully !");
	SPV::Application app{};
	return app.Run();
	
}

#elif SP_PLATFORM_DARWIN

int main(int argc, char** argv) 
{
	SPV::Logger::Init();
	SP_APP_INFO("Logger Initialized successfully !");
	SPV::Application app{};
	return app.Run();
}

#endif