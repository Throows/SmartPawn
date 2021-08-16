#pragma once

#include "SPpch.h"
#include "SimGameState.h"
#include "MenuState.h"

namespace SP {

	class Application
	{
	public:
		Application(const unsigned int width = 960, const unsigned int height = 480);
		virtual ~Application();
		void Run();
		void ProcessEvents();

	protected:
		void AddState(std::shared_ptr<State> State) {states.push_back(State);}

	private:
		unsigned int m_width;
		unsigned int m_height;
		bool m_running = true;
		std::shared_ptr<sf::RenderWindow> window;

		std::vector<std::shared_ptr<State>> states;


		void Init();
		void RegisterCallbacks();
	};
}