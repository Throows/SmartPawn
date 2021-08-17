#include "MenuState.h"

namespace SP
{
	MenuState::MenuState() : State("MenuState")
	{
	}

	void MenuState::OnUpdate(sf::RenderWindow& window)
	{

	}

	void MenuState::OnRender(sf::RenderTarget& target)
	{
		target.clear(sf::Color::Blue);
	}

	void MenuState::InitState()
	{
	}
}
