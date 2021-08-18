#include "MenuState.h"
#include "SimGameState.h"

namespace SP
{
	MenuState::MenuState(StatesPtr states, WindowPtr window) : State("MenuState")
	{

		this->states = std::move(states);
		this->window = std::move(window);
		InitState();
	}

	void MenuState::OnUpdate()
	{
		sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*this->window.get()));
		for (auto button : this->buttons)
		{
			button.Update(mousePos);
			if (button.IsClicked()) {
				this->states->push_back(std::make_shared<SimGameState>(states, this->window));
				this->SetExitedState();
			}
		}
	}

	void MenuState::OnRender()
	{

		this->window->draw(*this->background);

		this->window->draw(this->title);

		for (auto button : this->buttons)
		{
			button.Render(*this->window);
		}
	}

	void MenuState::InitState()
	{

		this->font = std::make_shared<sf::Font>();
		if (!this->font->loadFromFile("resources/fonts/neuropol_x_rg.ttf"))
		{
			SP_APP_ERROR("Could not load the font ! (SimGameState)");
		}

		this->textures.emplace("BUTTON_TEXTURE", std::make_shared<sf::Texture>());
		if (!this->textures.at("BUTTON_TEXTURE")->loadFromFile("resources/gui/buttons.png"))
		{
			SP_APP_ERROR("Could not load texture !");
		}

		this->textures.emplace("BACKGROUND_TEXTURE", std::make_shared<sf::Texture>());
		if (!this->textures.at("BACKGROUND_TEXTURE")->loadFromFile("resources/backgrounds/bg1.jpg"))
		{
			SP_APP_ERROR("Could not load texture !");
		}

		this->background = std::make_unique<sf::Sprite>();
		this->background->setTexture(*this->textures.at("BACKGROUND_TEXTURE"));
		this->background->setTextureRect(static_cast<sf::IntRect>(this->window->getViewport(this->window->getView())));

		this->title = sf::Text("SmartPawn - Game", *this->font, 50);
		this->title.setPosition(sf::Vector2f(250.0f, 50.0f));
		this->title.setStyle(sf::Text::Style::Bold);
		this->title.setColor(sf::Color::Black);
		this->title.setOutlineColor(sf::Color::White);
		this->title.setOutlineThickness(2.0f);

		Button startSimButton(sf::Vector2f(60.0f, 300.0f), sf::Vector2i(512, 128), std::string("Lancer la simulation"), *this->font, *this->textures.at("BUTTON_TEXTURE"), sf::Vector2i(0, 0), sf::Vector2i(0, 128), sf::Vector2i(0, 256));
		this->buttons.push_back(startSimButton);

	}
}
