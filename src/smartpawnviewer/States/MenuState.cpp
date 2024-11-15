#include "MenuState.hpp"
#include "SimGameState.hpp"
#include "ReplayState.hpp"
#include <filesystem>

namespace SPV
{
	
MenuState::MenuState(StateArgs* args) 
	: State(args, "MenuState")
{
}

MenuState::~MenuState()
{
	this->textures.clear();
}

void MenuState::OnUpdate()
{
	if (this->IsExitedState() || !this->IsInitializedState()) return;
	if (!isFocused) {
		UpdateListViewButton();
		isFocused = true;
	}
	sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*this->m_stateArgs->window.get()));
	for (auto button : this->buttons) {
		button.Update(mousePos);
		if (button.IsClicked()) {
			this->m_stateArgs->states->push_back(std::make_unique<SimGameState>(this->m_stateArgs));
			this->isFocused = false;
			//this->SetExitedState();
		}
	}
	this->recordListView->OnUpdate(*this->m_stateArgs->window);
	if (this->recordListView->hasClickedButton) {
		std::string clickedButton = this->recordListView->GetClickedButton();
		this->m_stateArgs->states->push_back(std::make_unique<ReplayState>(this->m_stateArgs, clickedButton));
		this->isFocused = false;
		//this->SetExitedState();
	}
}

void MenuState::OnRender()
{
	if (this->IsExitedState() || !this->IsInitializedState()) return;
	this->m_stateArgs->window->draw(*this->background);
	this->m_stateArgs->window->draw(this->title);
	for (auto button : this->buttons) {
		button.Render(*this->m_stateArgs->window);
	}
	this->recordListView->OnRender(*this->m_stateArgs->window);
}

void MenuState::ProcessEvents(sf::Event& event)
{
	this->recordListView->ProcessEvents(event);
}

void MenuState::UpdateListViewButton()
{
	this->recordListView->ResetButtons();
	if (!std::filesystem::exists("Records/")) {
		std::filesystem::create_directory("Records/");
	}
	try {
		int buttonOffset = 60.0f;
		for (const auto& entry : std::filesystem::directory_iterator("Records/")) {
			std::string buttonName(entry.path().stem().string());
			std::shared_ptr<ListViewButton> viewButton = std::make_shared<ListViewButton>(sf::Vector2f(610.0f, buttonOffset), sf::Vector2f(260.0f, 50.0f), *this->font, buttonName);
			this->recordListView->AddButton(viewButton);
			buttonOffset += 60.0f;
		}
	}
	catch (const std::exception& e) {
		SPV_APP_ERROR("Could not load the records ! (MenuState) {0}", e.what());
	}
}

void MenuState::InitState()
{
	this->font = std::make_shared<sf::Font>();
	if (!this->font->loadFromFile("Resources/Fonts/neuropol_x_rg.ttf")) {
		SPV_APP_ERROR("Could not load the font ! (SimGameState)");
	}

	this->textures.emplace("BUTTON_TEXTURE", std::make_shared<sf::Texture>());
	if (!this->textures.at("BUTTON_TEXTURE")->loadFromFile("Resources/GUI/buttons.png")) {
		SPV_APP_ERROR("Could not load texture !");
	}

	this->textures.emplace("BACKGROUND_TEXTURE", std::make_shared<sf::Texture>());
	if (!this->textures.at("BACKGROUND_TEXTURE")->loadFromFile("Resources/Backgrounds/bg1.jpg")) {
		SPV_APP_ERROR("Could not load texture !");
	}
	
	this->background = std::make_unique<sf::Sprite>();
	this->background->setTexture(*this->textures.at("BACKGROUND_TEXTURE"));
	this->background->setTextureRect(static_cast<sf::IntRect>(this->m_stateArgs->window->getViewport(this->m_stateArgs->window->getView())));
	auto titleText = this->m_stateArgs->config->GetText("title") + "\n" + this->m_stateArgs->config->GetText("description");
	this->title = sf::Text(titleText, *this->font, 50);
	this->title.setPosition(sf::Vector2f(50.0f, 50.0f));
	this->title.setStyle(sf::Text::Style::Bold);
	this->title.setFillColor(sf::Color::Black);
	this->title.setOutlineColor(sf::Color::White);
	this->title.setOutlineThickness(2.0f);
	Button startSimButton(sf::Vector2f(50.0f, 300.0f), sf::Vector2i(512, 128), this->m_stateArgs->config->GetText("launch"), *this->font, *this->textures.at("BUTTON_TEXTURE"), sf::Vector2i(0, 0), sf::Vector2i(0, 128), sf::Vector2i(0, 256));
	this->buttons.push_back(startSimButton);
	this->recordListView = std::make_shared<ListView>(sf::Vector2f(600.0f, 50.0f), sf::Vector2f(300.0f, 400.0f));
	UpdateListViewButton();

	this->isFocused = true;
	this->isInitialized = true;
}

} // Namespace SPV
