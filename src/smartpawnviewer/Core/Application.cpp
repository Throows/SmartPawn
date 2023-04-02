#include "Application.hpp"

namespace SPV
{

Application::Application(const unsigned int width, const unsigned int height)
{
	this->m_width = width;
	this->m_height = height;

	this->m_stateArgs.window = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), "Application", sf::Style::Default);
	this->m_stateArgs.states = std::make_unique<std::vector<std::unique_ptr<SPV::State>>>();
	this->m_stateArgs.config = std::make_unique<SPV::Configuration>();
	
	this->m_stateArgs.states->push_back(std::make_unique<MenuState>(&this->m_stateArgs));
	this->Init();
}

int Application::Run()
{
	while (m_running) {
		std::vector<std::unique_ptr<State>>::const_iterator it = this->m_stateArgs.states->begin();
		while (it != this->m_stateArgs.states->end()) {
			if ((*it)->IsExitedState()) {
				it = this->m_stateArgs.states->erase(it);
			}
			else if (!(*it)->IsInitializedState()){
				(*it)->InitState();
				this->m_clock.restart();
				it++;
			}
			else {
				it++;
			}
		}

		int dt = this->m_clock.restart().asMilliseconds();
		ProcessAppEvents();

		this->m_stateArgs.window->clear();
		if (!this->m_stateArgs.states->empty()) {
			this->m_stateArgs.states->back()->OnUpdate(dt);
			this->m_stateArgs.states->back()->OnRender();
		}
		else {
			m_running = false;
		}
		this->m_stateArgs.window->display();
	}
	this->m_stateArgs.window->close();
	return 0;
}

void Application::ProcessAppEvents()
{
	sf::Event event;
	while (this->m_stateArgs.window->pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			m_running = false;

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			this->m_stateArgs.states->back()->SetExitedState();
	}

	if (!this->m_stateArgs.states->empty()) {
		this->m_stateArgs.states->back()->ProcessEvents(event);
	}
}

void Application::Init()
{
	this->m_stateArgs.config->LoadConfiguration();
	this->m_stateArgs.window->setFramerateLimit(60);

	this->m_stateArgs.window->setTitle(this->m_stateArgs.config->GetText("title") + " - " + this->m_stateArgs.config->GetText("description"));
}

void Application::RegisterCallbacks()
{
	
}

} // Namespace SPV