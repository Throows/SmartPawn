#pragma once
#include "State.h"

namespace SP
{
	class MenuState : public State
	{
	public:
		MenuState();
		~MenuState() = default;

		virtual void OnUpdate(sf::RenderWindow& window) override;
		virtual void OnRender(sf::RenderTarget& target) override;

	private:
		void InitState();
	};
}