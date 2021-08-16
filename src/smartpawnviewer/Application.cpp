#include "Application.h"

namespace SP{

	Application::Application(const unsigned int width, const unsigned int height)
	{
		this->m_width = width;
		this->m_height = height;

		this->window = std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height), "SmartPawn - Le jeux de l'IA", sf::Style::Default);

		AddState(std::make_shared<SimGameState>(window));
		AddState(std::make_shared<MenuState>(window));

		this->Init();

	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (m_running) {

			ProcessEvents();


			if (this->states.back()->isExitedState()) {
				SP_APP_INFO("popped !");
				this->states.pop_back();
			}

			if (!this->states.empty())
			{
				this->states.back()->OnUpdate();
				this->states.back()->OnRender();
			}
			else
			{
				m_running = false;
			}
			this->window.get()->display();
		}

		this->window.get()->close();
		
	}

	void Application::ProcessEvents()
	{
		sf::Event event;
		while (window.get()->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				m_running = false;

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				this->states.back()->SetExitedState();

		}
	}

	void Application::Init()
	{
	}

	void Application::RegisterCallbacks()
	{
		
	}
}