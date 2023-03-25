#include "Application.hpp"

namespace SPV
{

Application::Application(const unsigned int width, const unsigned int height)
{
	this->m_width = width;
	this->m_height = height;

	this->window = std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height), "Application", sf::Style::Default);
	this->states = std::make_shared<std::vector<std::shared_ptr<State>>>();
	AddState(std::make_shared<MenuState>(this->states, this->window));
	this->m_config = std::make_shared<SPV::Configuration>();
	this->Init();
}

int Application::Run()
{
	while (m_running) {

		std::vector<std::shared_ptr<State>>::const_iterator it = this->states->begin();
		while (it != this->states->end()) {
			if ((*it)->IsExitedState()) {
				it = this->states->erase(it);
			}
			else if (!(*it)->IsInitializedState()){
				(*it)->InitState(this->m_config);
				it++;
			}
			else {
				it++;
			}
		}

		ProcessAppEvents();

		this->window->clear();
		if (!this->states->empty()) {
			this->states->back()->OnUpdate();
			this->states->back()->OnRender();
		}
		else {
			m_running = false;
		}
		this->window->display();
	}
	this->window->close();
	return 0;
}

void Application::ProcessAppEvents()
{
	sf::Event event;
	while (this->window->pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			m_running = false;

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			this->states->back()->SetExitedState();
	}

	if (!this->states->empty()) {
		this->states->back()->ProcessEvents(event);
	}
}

void Application::Init()
{
	this->m_config->LoadConfiguration();
	this->window->setFramerateLimit(60);

	this->window->setTitle(this->m_config->GetText("title") + " - " + this->m_config->GetText("description"));
}

void Application::RegisterCallbacks()
{
	
}

} // Namespace SPV