#include "SimGameState.hpp"

namespace SPV
{
	
SimGameState::SimGameState(StateArgs* args) 
	: State(args, "SimGameState")
{
}

void SimGameState::OnUpdate(const int& dt)
{
	if (this->IsExitedState() || !this->IsInitializedState()) return;
	sf::Time time = clock.getElapsedTime();
	if (time.asMilliseconds() >= 10) {
		if (!this->engine->GetData()->IsGameEnded()) {
			this->engine->PlayNextTurn();
			progressBar->SetProgress(engine->GetPercentageEnded());
		}
		clock.restart();
	}
	progressBar->OnUpdate(*this->m_stateArgs->window);
}

void SimGameState::OnRender()
{
	if (this->IsExitedState() || !this->IsInitializedState()) return;
	this->m_stateArgs->window->draw(*this->background);
	progressBar->OnRender(*this->m_stateArgs->window);
}
void SimGameState::ProcessEvents(sf::Event& event)
{
	(void)event;
}

void SimGameState::SetExitedState()
{
	this->isExited = true;
	this->engine->GetData()->SetEnded(true);
}

void SimGameState::InitState()
{
	this->textures.emplace("BACKGROUND_TEXTURE", std::make_shared<sf::Texture>());
	if (!this->textures.at("BACKGROUND_TEXTURE")->loadFromFile("Resources/Backgrounds/bg2.jpg")) {
		SPV_APP_ERROR("Could not load texture !");
	}
	this->textures.emplace("PBB_TEXTURE", std::make_shared<sf::Texture>());
	if (!this->textures.at("PBB_TEXTURE")->loadFromFile("Resources/GUI/progress_bar_bg.png")) {
		SPV_APP_ERROR("Could not load texture !");
	}
	this->textures.emplace("PB_TEXTURE", std::make_shared<sf::Texture>());
	if (!this->textures.at("PB_TEXTURE")->loadFromFile("Resources/GUI/progressbar.png")) {
		SPV_APP_ERROR("Could not load texture !");
	}
	this->progressBar = std::make_shared<ProgressBar>(sf::Vector2f(330.0f, 150.0f), sf::Vector2i(300.0f, 60.0f), *this->textures.at("PBB_TEXTURE"), *this->textures.at("PB_TEXTURE"));
	this->textures.at("BACKGROUND_TEXTURE")->setSmooth(true);
	this->background = std::make_unique<sf::Sprite>(*this->textures.at("BACKGROUND_TEXTURE"), this->m_stateArgs->window->getViewport(this->m_stateArgs->window->getView()));
	this->background->setScale(sf::Vector2f(2.0f, 2.0f));
	auto settings = this->m_stateArgs->config->GetSettings();
	this->engine = std::make_shared<SP::SPGame>(settings.initialPawnNB, settings.gridWidth, settings.gridHeight, settings.tieMoveNumber);
	this->engine->InitGame();
	this->isInitialized = true;
}

} // Namespace SPV