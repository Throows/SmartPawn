#include "MenuState.hpp"
#include "SimGameState.hpp"
#include "ReplayState.hpp"
#include <filesystem>

namespace SPV
{
	
MenuState::MenuState(StatesPtr states, WindowPtr window) : State("MenuState")
{
	this->states = states;
	this->window = window;
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
	sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*this->window.get()));
	for (auto button : this->buttons) {
		button.Update(mousePos);
		if (button.IsClicked()) {
			this->states->push_back(std::make_shared<SimGameState>(states, this->window));
			this->isFocused = false;
			//this->SetExitedState();
		}
	}
	this->recordListView->OnUpdate(*this->window);
	if (this->recordListView->hasClickedButton) {
		std::string clickedButton = this->recordListView->GetClickedButton();
		this->states->push_back(std::make_shared<ReplayState>(states, this->window, clickedButton));
		this->isFocused = false;
		//this->SetExitedState();
	}
}

void MenuState::OnRender()
{
	if (this->IsExitedState() || !this->IsInitializedState()) return;
	this->window->draw(*this->background);
	this->window->draw(this->title);
	for (auto button : this->buttons) {
		button.Render(*this->window);
	}
	this->recordListView->OnRender(*this->window);
}

void MenuState::ProcessEvents(sf::Event& event)
{
	this->recordListView->ProcessEvents(event);
}

void MenuState::UpdateListViewButton()
{
	this->recordListView->ResetButtons();
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

void MenuState::InitState(ResourceAllocator* allocator)
{
	this->font = std::make_shared<sf::Font>();
	if (!this->font->loadFromFile(allocator->GetFontPath("neuropol_x_rg.ttf"))) {
		SPV_APP_ERROR("Could not load the font ! (SimGameState)");
	}

	this->textures.emplace("BUTTON_TEXTURE", std::make_shared<sf::Texture>());
	if (!this->textures.at("BUTTON_TEXTURE")->loadFromFile(allocator->GetGUITexturePath("buttons.png"))) {
		SPV_APP_ERROR("Could not load texture !");
	}

	this->textures.emplace("BACKGROUND_TEXTURE", std::make_shared<sf::Texture>());
	if (!this->textures.at("BACKGROUND_TEXTURE")->loadFromFile(allocator->GetBackgroundPath("bg1.jpg"))) {
		SPV_APP_ERROR("Could not load texture !");
	}
	
	this->background = std::make_unique<sf::Sprite>();
	this->background->setTexture(*this->textures.at("BACKGROUND_TEXTURE"));
	this->background->setTextureRect(static_cast<sf::IntRect>(this->window->getViewport(this->window->getView())));
	this->title = sf::Text("SmartPawn\n The Game", *this->font, 50);
	this->title.setPosition(sf::Vector2f(50.0f, 50.0f));
	this->title.setStyle(sf::Text::Style::Bold);
	this->title.setFillColor(sf::Color::Black);
	this->title.setOutlineColor(sf::Color::White);
	this->title.setOutlineThickness(2.0f);
	Button startSimButton(sf::Vector2f(50.0f, 300.0f), sf::Vector2i(512, 128), std::string("Lancer la simulation"), *this->font, *this->textures.at("BUTTON_TEXTURE"), sf::Vector2i(0, 0), sf::Vector2i(0, 128), sf::Vector2i(0, 256));
	this->buttons.push_back(startSimButton);
	this->recordListView = std::make_shared<ListView>(sf::Vector2f(600.0f, 50.0f), sf::Vector2f(300.0f, 400.0f));
	UpdateListViewButton();

	this->isFocused = true;
	State::InitState(allocator);
}

} // Namespace SPV
