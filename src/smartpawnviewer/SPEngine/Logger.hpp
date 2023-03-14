#pragma once
#include <spdlog/spdlog.h>

namespace SP
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

} // Namespace SP

#define SPV_APP_TRACE(...)         ::SP::Logger::GetAppLogger()->trace(__VA_ARGS__)
#define SPV_APP_INFO(...)          ::SP::Logger::GetAppLogger()->info(__VA_ARGS__)
#define SPV_APP_WARN(...)          ::SP::Logger::GetAppLogger()->warn(__VA_ARGS__)
#define SPV_APP_ERROR(...)         ::SP::Logger::GetAppLogger()->error(__VA_ARGS__)
#define SPV_APP_CRITICAL(...)      ::SP::Logger::GetAppLogger()->critical(__VA_ARGS__)

#define SP_ENGINE_TRACE(...)         ::SP::Logger::GetEngineLogger()->trace(__VA_ARGS__)
#define SP_ENGINE_INFO(...)          ::SP::Logger::GetEngineLogger()->info(__VA_ARGS__)
#define SP_ENGINE_WARN(...)          ::SP::Logger::GetEngineLogger()->warn(__VA_ARGS__)
#define SP_ENGINE_ERROR(...)         ::SP::Logger::GetEngineLogger()->error(__VA_ARGS__)
#define SP_ENGINE_CRITICAL(...)      ::SP::Logger::GetEngineLogger()->critical(__VA_ARGS__)