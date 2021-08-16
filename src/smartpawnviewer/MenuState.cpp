#include "MenuState.h"

namespace SP
{
	MenuState::MenuState(std::shared_ptr<sf::RenderWindow> window) : State("MenuState", window)
	{
	}

	void MenuState::OnUpdate()
	{

	}

	void MenuState::OnRender()
	{
		this->window.get()->clear(sf::Color::Blue);
	}

	void MenuState::InitState()
	{
	}
}
