#pragma once
#include "State.h"

namespace SP
{
	class MenuState : public State
	{
	public:
		MenuState(std::shared_ptr<sf::RenderWindow> window);
		~MenuState() = default;

		virtual void OnUpdate() override;
		virtual void OnRender() override;

	private:
		void InitState();
	};
}