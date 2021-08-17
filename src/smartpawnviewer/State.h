#pragma once
#include "SPpch.h"

namespace SP
{
	class State
	{
	public:
		State(const std::string& name);
		virtual ~State() = default;

		virtual void OnUpdate(sf::RenderWindow& window) {}
		virtual void OnRender(sf::RenderTarget& target) {}

		virtual bool isExitedState() { return this->isExited; }
		virtual void SetExitedState() { isExited = true; }
		
		virtual std::string GetName() { return this->m_StateName; }

	protected:
		std::string m_StateName;
		bool isExited = false;

		virtual void InitState() {}
	};
}