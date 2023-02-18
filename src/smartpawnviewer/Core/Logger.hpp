#pragma once
#include <spdlog/spdlog.h>

namespace SPV
{
class Logger
{
public:
	static void Init();
	static std::shared_ptr<spdlog::logger>& GetEngineLogger() { return s_EngineLogger; }
	static std::shared_ptr<spdlog::logger>& GetAppLogger() { return s_AppLogger; }

private:
	static std::shared_ptr<spdlog::logger> s_EngineLogger;
	static std::shared_ptr<spdlog::logger> s_AppLogger;
};

} // Namespace SPV

#define SP_APP_TRACE(...)         ::SPV::Logger::GetAppLogger()->trace(__VA_ARGS__)
#define SP_APP_INFO(...)          ::SPV::Logger::GetAppLogger()->info(__VA_ARGS__)
#define SP_APP_WARN(...)          ::SPV::Logger::GetAppLogger()->warn(__VA_ARGS__)
#define SP_APP_ERROR(...)         ::SPV::Logger::GetAppLogger()->error(__VA_ARGS__)
#define SP_APP_CRITICAL(...)      ::SPV::Logger::GetAppLogger()->critical(__VA_ARGS__)
