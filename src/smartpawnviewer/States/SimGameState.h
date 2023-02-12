#pragma once

#include "State.h"
#include <GUI/ProgressBar.h>
#include <SPEngine.h>

namespace SP
{
	class SimGameState : public State
	{
	public:
		SimGameState(StatesPtr states, WindowPtr window);
		~SimGameState();

		virtual void OnUpdate() override;
		virtual void OnRender() override;
		void ProcessEvents(sf::Event& event) override;
		virtual void SetExitedState() override;

	private:
		void InitState();

		std::shared_ptr<SP::ProgressBar> progressBar;

		sf::Clock clock;

		std::shared_ptr<SP::SPGame> engine;

		std::vector<sf::Text> title;
		std::unique_ptr<sf::Sprite> background;
		std::map<std::string, std::shared_ptr<sf::Texture>> textures;
		std::shared_ptr<sf::Font> font;

	};
} // Namespace SP