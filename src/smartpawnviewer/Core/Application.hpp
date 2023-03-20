#pragma once
#include <Core/pch.hpp>
#include <Core/LocaleText.hpp>
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

protected:
	void AddState(std::shared_ptr<SPV::State> state) { states->push_back(state); } 

private:
	unsigned int m_width;
	unsigned int m_height;
	bool m_running = true;

	std::shared_ptr<sf::RenderWindow> window;
	StatesPtr states;
	std::shared_ptr<SPV::LocaleText> locale;


	void Init();
	void RegisterCallbacks();
};

} // Namespace SPV