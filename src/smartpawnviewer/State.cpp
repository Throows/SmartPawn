#include "State.h"
namespace SP
{
	State::State(const std::string& name, std::shared_ptr<sf::RenderWindow> window)
	{
		this->m_StateName = name;
		this->window = window;
		isExited = false;
	}
}
