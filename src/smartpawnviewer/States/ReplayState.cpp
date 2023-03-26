#include "ReplayState.hpp"

namespace SPV
{

ReplayState::ReplayState(StateArgs* args, const std::string& recordFile) 
	: State(args, "ReplayState")
	, reader(recordFile)
{
}

ReplayState::~ReplayState()
{
	this->textures.clear();
}

void ReplayState::OnUpdate()
{
	if (this->IsExitedState() || !this->IsInitializedState()) return;
	bool oldState = isReplay;
	if (isReplay) {
		UpdateReplay();
	}
	if (!isReplay && oldState) {
		this->title.setString(this->m_stateArgs->config->GetFormatedText("winner", this->reader.GetWinner()));
	}
}

void ReplayState::OnRender()
{
	if (this->IsExitedState() || !this->IsInitializedState()) return;
	this->m_stateArgs->window->draw(*this->background);
	this->m_stateArgs->window->draw(*this->grid);
	for (auto& pawn : this->pawns) {
		pawn->OnRender(*this->m_stateArgs->window);
	}
	this->m_stateArgs->window->draw(this->title);
}

void ReplayState::ProcessEvents(sf::Event& event)
{
	(void)event;
}

bool ReplayState::ExistPawn(int x, int y)
{
	return this->reader.ExistPawn(x, y);
}

Pawn* ReplayState::GetPawn(int x, int y)
{
	for (auto pawn : this->pawns) {
		if (pawn->IsCoords(x, y)) return pawn.get();
	}
	return nullptr;
}

void ReplayState::RemovePawn(int x, int y)
{
	auto it = this->pawns.begin();
	while (it != this->pawns.end()) {
		if ((*it)->IsCoords(x, y)) {
			it = this->pawns.erase(it);
		}
		else {
			it++;
		}
	}
}

void ReplayState::InitState()
{
	this->font = std::make_shared<sf::Font>();
	if (!this->font->loadFromFile("Resources/Fonts/neuropol_x_rg.ttf")) {
		SPV_APP_ERROR("Could not load the font ! (SimGameState)");
	}

	this->textures.emplace("PAWN_TEXTURE", std::make_shared<sf::Texture>());
	if (!this->textures.at("PAWN_TEXTURE")->loadFromFile("Resources/GUI/pawns.png")) {
		SPV_APP_ERROR("Could not load texture !");
	}

	this->textures.emplace("GRID_TEXTURE", std::make_shared<sf::Texture>());
	if (!this->textures.at("GRID_TEXTURE")->loadFromFile("Resources/Backgrounds/grid_bg.png")) {
		SPV_APP_ERROR("Could not load texture !");
	}

	this->textures.emplace("BACKGROUND_TEXTURE", std::make_shared<sf::Texture>());
	if (!this->textures.at("BACKGROUND_TEXTURE")->loadFromFile("Resources/Backgrounds/bg1.jpg")) {
		SPV_APP_ERROR("Could not load texture !");
	}

	this->background = std::make_unique<sf::Sprite>();
	this->background->setTexture(*this->textures.at("BACKGROUND_TEXTURE"));
	this->background->setTextureRect(static_cast<sf::IntRect>(this->m_stateArgs->window->getViewport(this->m_stateArgs->window->getView())));
	this->grid = std::make_unique<sf::Sprite>();
	this->grid->setPosition(sf::Vector2f(50.0f, 40.0f));
	this->grid->setTexture(*this->textures.at("GRID_TEXTURE"));
	this->reader.ReadSimulate();
	
	std::vector<uint8_t> board = this->reader.GetBoard();
	int width = this->reader.GetWidth();
	int id = 0, x, y;
	for (const auto &p : board) {
		x = id % width;
		y = id / width;
		if (p != 0) {
			std::shared_ptr<Pawn> pawn = std::make_shared<Pawn>(x, y, this->textures.at("PAWN_TEXTURE"), p == 1 ? 0 : 35);
			this->pawns.push_back(std::move(pawn));
		}
		id++;
	}
	this->title = sf::Text("", *this->font, 30);
	this->title.setPosition(sf::Vector2f(475.f, 50.0f));
	this->title.setFillColor(sf::Color::Black);
	this->title.setOutlineColor(sf::Color::White);
	this->title.setOutlineThickness(1.5f);
	this->isInitialized = true;
}

void ReplayState::UpdateReplay()
{
	sf::Time time = clock.getElapsedTime();
	if (time.asMilliseconds() >= 50) {
		if (this->reader.HasNext()) {
			Action action = this->reader.GetNextAction();
			Pawn *movePawn = ReplayState::GetPawn(action.fromX, action.fromY);
			if (movePawn == nullptr) {
				SPV_APP_ERROR("Pawn not found !");
			}
			Pawn *attackedPawn = ReplayState::GetPawn(action.toX, action.toY);
			if (attackedPawn != nullptr) {
				ReplayState::RemovePawn(action.toX, action.toY);
			}
			movePawn->SetCoords(action.toX, action.toY); // No error check (Supposed to be valid)
			this->reader.UpdateBoard();
		}
		else {
			isReplay = false;
		}
		clock.restart();
	}
}

} // Namespace SPV