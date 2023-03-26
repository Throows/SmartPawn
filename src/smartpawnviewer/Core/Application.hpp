#pragma once
#include <Core/pch.hpp>
#include <Core/Configuration.hpp>
#include <States/MenuState.hpp>

namespace SPV
{
class Application
{
public:
	Application(const unsigned int width = 960, const unsigned int height = 480);
	virtual ~Application() = default;

	int Run();
	void ProcessAppEvents();

private:
	unsigned int m_width;
	unsigned int m_height;
	bool m_running = true;
	StateArgs m_stateArgs;

	void Init();
	void RegisterCallbacks();
};

} // Namespace SPV