#pragma once
#include "State.h"
#include "ProgressBar.h"

namespace SP
{
	class SimGameState : public State
	{
	public:
		SimGameState(StatesPtr states, WindowPtr window);
		~SimGameState() = default;

		virtual void OnUpdate() override;
		virtual void OnRender() override;

	private:
		void InitState();

		std::shared_ptr<SP::ProgressBar> progressBar;

		sf::Clock clock;

		//TODO mutltiple text during game simulation
		sf::Text title;
		std::unique_ptr<sf::Sprite> background;
		std::map<std::string, std::shared_ptr<sf::Texture>> textures;
		std::shared_ptr<sf::Font> font;

	};
}