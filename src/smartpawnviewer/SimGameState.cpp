#include "SimGameState.h"

namespace SP
{
	SimGameState::SimGameState(StatesPtr states, WindowPtr window) : State("SimGameState")
	{
		this->states = std::move(states);
		this->window = std::move(window);
		InitState();
	}

	void SimGameState::OnUpdate()
	{

		
	}

	void SimGameState::OnRender()
	{
		
		this->window->draw(*this->background);
	}

	void SimGameState::InitState()
	{
		this->textures.emplace("BACKGROUND_TEXTURE", std::make_shared<sf::Texture>());
		if (!this->textures.at("BACKGROUND_TEXTURE")->loadFromFile("resources/backgrounds/bg2.jpg"))
		{
			SP_APP_ERROR("Could not load texture !");
		}

		this->textures.at("BACKGROUND_TEXTURE")->setSmooth(true);
		this->background = std::make_unique<sf::Sprite>(*this->textures.at("BACKGROUND_TEXTURE"), static_cast<sf::IntRect>(this->window->getViewport(this->window->getView())));
		this->background->setScale(sf::Vector2f(2.0f, 2.0f));
	}
}