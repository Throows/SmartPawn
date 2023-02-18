#include <Core/pch.hpp>
#include "Core/Application.hpp"

#ifdef SP_PLATFORM_WIN

int main(int argc, char** argv) 
{
	SPV::Logger::Init();
	SP_APP_INFO("Logger Initialized successfully !");
	SPV::Application app{};
	app.Run();
}

#elif SP_PLATFORM_DARWIN

int main(int argc, char** argv) 
{
	SPV::Logger::Init();
	SP_APP_INFO("Logger Initialized successfully !");
	SPV::Application app{};
	app.Run();
}

#endif