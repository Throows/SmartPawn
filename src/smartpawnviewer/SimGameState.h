#pragma once
#include "State.h"

namespace SP
{
	class SimGameState : public State
	{
	public:
		SimGameState(std::shared_ptr<sf::RenderWindow> window);
		~SimGameState() = default;

		virtual void OnUpdate() override;
		virtual void OnRender() override;

	private:
		void InitState();
	};
}