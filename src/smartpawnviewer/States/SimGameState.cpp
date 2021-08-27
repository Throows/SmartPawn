#include "SimGameState.h"

extern std::shared_ptr<SP::SimEngine> CreateEngine();

namespace SP
{
	SimGameState::SimGameState(StatesPtr states, WindowPtr window) : State("SimGameState")
	{
		this->states = std::move(states);
		this->window = std::move(window);
		InitState();
	}

	SimGameState::~SimGameState()
	{
	}

	void SimGameState::OnUpdate()
	{
		sf::Time time = clock.getElapsedTime();

		if (time.asMilliseconds() >= 60) {
			if (!this->engine->isEnded()) {
				this->engine->PlayNextTurn();
				progressBar->SetProgress(engine->GetPercentageEnded());
			}
			clock.restart();
		}

		progressBar->OnUpdate(*this->window);
	}

	void SimGameState::OnRender()
	{
		this->window->draw(*this->background);
		progressBar->OnRender(*this->window);
	}

	void SimGameState::ProcessEvents(sf::Event& event)
	{
	}

	void SimGameState::InitState()
	{
		this->textures.emplace("BACKGROUND_TEXTURE", std::make_shared<sf::Texture>());
		if (!this->textures.at("BACKGROUND_TEXTURE")->loadFromFile("resources/backgrounds/bg2.jpg"))
		{
			SP_APP_ERROR("Could not load texture !");
		}

		this->textures.emplace("PBB_TEXTURE", std::make_shared<sf::Texture>());
		if (!this->textures.at("PBB_TEXTURE")->loadFromFile("resources/gui/progress_bar_bg.png"))
		{
			SP_APP_ERROR("Could not load texture !");
		}

		this->textures.emplace("PB_TEXTURE", std::make_shared<sf::Texture>());
		if (!this->textures.at("PB_TEXTURE")->loadFromFile("resources/gui/progressbar.png"))
		{
			SP_APP_ERROR("Could not load texture !");
		}


		this->progressBar = std::make_shared<ProgressBar>(sf::Vector2f(330.0f, 150.0f), sf::Vector2i(300.0f, 60.0f), *this->textures.at("PBB_TEXTURE"), *this->textures.at("PB_TEXTURE"));

		this->textures.at("BACKGROUND_TEXTURE")->setSmooth(true);
		this->background = std::make_unique<sf::Sprite>(*this->textures.at("BACKGROUND_TEXTURE"), static_cast<sf::IntRect>(this->window->getViewport(this->window->getView())));
		this->background->setScale(sf::Vector2f(2.0f, 2.0f));

		
		this->engine = std::move(CreateEngine());
		this->engine->InitEngine();
		
	}
}