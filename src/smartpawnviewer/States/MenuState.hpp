#pragma once

#include "State.hpp"
#include <GUI/Button.hpp>
#include <GUI/ListView.hpp>

namespace SPV
{

class MenuState : public State
{
public:
	MenuState(StateArgs* args);
	~MenuState();
	void OnUpdate() override;
	void OnRender() override;
	void ProcessEvents(sf::Event& event) override;
	void UpdateListViewButton();
	void InitState() override;

private:
	std::vector<Button> buttons;
	std::shared_ptr<ListView> recordListView;
	sf::Text title;
	std::unique_ptr<sf::Sprite> background;
	std::map<std::string, std::shared_ptr<sf::Texture>> textures;
	std::shared_ptr<sf::Font> font;
	bool isFocused;
};

} // Namespace SPV