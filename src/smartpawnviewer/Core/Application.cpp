#include "Application.h"

namespace SP{

	Application::Application(const unsigned int width, const unsigned int height)
	{
		this->m_width = width;
		this->m_height = height;

		this->window = std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height), "SmartPawn - Le jeux de l'IA", sf::Style::Default);
		this->states = std::make_shared<std::vector<std::shared_ptr<State>>>();
		AddState(std::make_shared<MenuState>(this->states, this->window));

		this->Init();

	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (m_running) {

			std::vector<std::shared_ptr<State>>::const_iterator it = this->states->begin();

			while (it != this->states->end())
			{
				if ((*it)->isExitedState()) {
					it = this->states->erase(it);
				}
				else
				{
					it++;
				}
			}


			ProcessAppEvents();

			this->window->clear();
			if (!this->states->empty())
			{
				this->states->back()->OnUpdate();
				this->states->back()->OnRender();
			}
			else
			{
				m_running = false;
			}
			this->window->display();
		}

		this->window->close();
		
	}

	void Application::ProcessAppEvents()
	{
		
		sf::Event event;
		while (this->window->pollEvent(event))
		{
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
		this->window->setFramerateLimit(60);
	}

	void Application::RegisterCallbacks()
	{
		
	}
}