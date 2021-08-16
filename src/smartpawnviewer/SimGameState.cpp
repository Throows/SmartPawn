#include "SimGameState.h"

namespace SP
{
	SimGameState::SimGameState(std::shared_ptr<sf::RenderWindow> window) : State("SimGameState",  window)
	{

	}

	void SimGameState::OnUpdate()
	{
	}

	void SimGameState::OnRender()
	{
		this->window.get()->clear(sf::Color::Red);
	}

	void SimGameState::InitState()
	{
	}
}