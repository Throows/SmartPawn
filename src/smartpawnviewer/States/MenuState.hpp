#pragma once

#include "States/State.hpp"
#include <GUI/Button.hpp>
#include <GUI/ListView.hpp>
#include <GUI/NeuronsTrace.hpp>

namespace SPV
{

class MenuState : public State
{
public:
	MenuState(StateArgs* args);
	~MenuState();
	void OnUpdate(const int& dt) override;
	void OnRender() override;
	void ProcessEvents(sf::Event& event) override;
	void InitState() override;

private:
	std::vector<Button> buttons;
	std::shared_ptr<ListView> recordListView;
	sf::Text title;
	std::map<std::string, std::shared_ptr<sf::Texture>> textures;
	std::shared_ptr<sf::Font> font;
	bool updateListView = true;
	NeuronsTrace traceTest;

	void CreateListButtons();
};

} // Namespace SPV