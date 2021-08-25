#pragma once

#include <Core/pch.h>
#include <States/SimGameState.h>
#include <States/MenuState.h>

namespace SP {

	class Application
	{
	public:
		Application(const unsigned int width = 960, const unsigned int height = 480);
		virtual ~Application();
		void Run();
		void ProcessEvents();

	protected:
		void AddState(std::shared_ptr<State> state) {states->push_back(state);}

	private:
		unsigned int m_width;
		unsigned int m_height;
		bool m_running = true;
		std::shared_ptr<sf::RenderWindow> window;

		std::shared_ptr<std::vector<std::shared_ptr<State>>> states;


		void Init();
		void RegisterCallbacks();
	};
}