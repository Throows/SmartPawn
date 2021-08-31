#include "ReplayState.h"

namespace SP
{
	ReplayState::ReplayState(StatesPtr states, WindowPtr window, const std::string& recordFile) : State("ReplayState"), reader(recordFile)
	{
		this->states = states;
		this->window = window;
		InitState();
	}

	ReplayState::~ReplayState()
	{
		this->textures.clear();
	}

	void ReplayState::OnUpdate()
	{
		sf::Time time = clock.getElapsedTime();
		if (time.asSeconds() <= 2)
		{
			if (this->reader.HasNext()) {
				Action action = this->reader.NextAction();
				
			}
			clock.restart();
		}

	}

	void ReplayState::OnRender()
	{
		this->window->draw(*this->background);
		this->window->draw(*this->grid);

		for (auto& pawn : this->pawns)
		{
			pawn->OnRender(*this->window);
		}
	}

	void ReplayState::ProcessEvents(sf::Event& event)
	{
	}

	void ReplayState::InitState()
	{

		this->textures.emplace("PAWN_TEXTURE", std::make_shared<sf::Texture>());
		if (!this->textures.at("PAWN_TEXTURE")->loadFromFile("resources/gui/pawns.png"))
		{
			SP_APP_ERROR("Could not load texture !");
		}

		this->textures.emplace("GRID_TEXTURE", std::make_shared<sf::Texture>());
		if (!this->textures.at("GRID_TEXTURE")->loadFromFile("resources/backgrounds/grid_bg.png"))
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

		this->grid = std::make_unique<sf::Sprite>();
		this->grid->setPosition(sf::Vector2f(50.0f, 40.0f));
		this->grid->setTexture(*this->textures.at("GRID_TEXTURE"));

		this->reader.ReadSimulate();
		
		std::vector<std::vector<int>> board = this->reader.GetBoard();
		int x = 0;
		int y = 0;
		for (auto& column : board)
		{
			for (auto& row : column)
			{
				if (row != 0) {
					std::unique_ptr<Pawn> pawn = std::make_unique<Pawn>(x, y, this->textures.at("PAWN_TEXTURE"), row == 1 ? 0 : 35);
					this->pawns.push_back(std::move(pawn));
				}
				y++;
			}
			x++;
		}
	}
}