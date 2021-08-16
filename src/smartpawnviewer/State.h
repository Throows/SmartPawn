#pragma once
#include "SPpch.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

namespace SP
{
	class State
	{
	public:
		State(const std::string& name, std::shared_ptr<sf::RenderWindow> window);
		virtual ~State() = default;

		virtual void OnUpdate() {}
		virtual void OnRender() {}

		virtual bool isExitedState() { return this->isExited; }
		virtual void SetExitedState() {
			isExited = true;
			SP_APP_INFO("Exited !");
		}
		
		virtual std::string GetName() { return this->m_StateName; }

	protected:
		std::string m_StateName;
		std::shared_ptr<sf::RenderWindow> window;
		bool isExited;

		virtual void InitState() {}
	};
}