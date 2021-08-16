#include "Application.h"

namespace SP{

	Application::Application(const unsigned int width, const unsigned int height)
	{
		this->m_width = width;
		this->m_height = height;
		this->layers.push_back(new SimGameLayer());
		this->layers.push_back(new MenuLayer());

		this->Init();

	}

	Application::~Application()
	{
		for (Layer* layer : this->layers)
		{
			delete layer;
		}
	}

	void Application::Run()
	{
		while (m_running) {

			if (this->layers.back()->isExitedState()) this->layers.pop_back();
			if (!this->layers.empty())
			{
				this->layers.back()->OnUpdate();
				this->layers.back()->OnRender();
			}
			else
			{
				m_running = false;
			}

		}

	}

	void Application::Init()
	{
	}

	void Application::RegisterCallbacks()
	{
		
	}
}