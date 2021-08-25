#pragma once
#include <Core/pch.h>

namespace SP
{
	class State
	{
	public:
		State(const std::string& name);
		virtual ~State();

		virtual void OnUpdate() {}
		virtual void OnRender() {}

		virtual bool isExitedState() { return this->isExited; }
		virtual void SetExitedState() { 
			isExited = true;
			SP_APP_INFO("State exited : {0}", m_StateName);
		}
		
		virtual std::string GetName() { return this->m_StateName; }


	protected:
		std::string m_StateName;
		bool isExited = false;
		std::shared_ptr<sf::RenderWindow> window;
		std::shared_ptr<std::vector<std::shared_ptr<State>>> states;

		virtual void InitState() {}
	};
}

typedef std::shared_ptr<std::vector<std::shared_ptr<SP::State>>> StatesPtr;
typedef std::shared_ptr<sf::RenderWindow> WindowPtr;