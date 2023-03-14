#pragma once
#include <Core/pch.hpp>

typedef std::shared_ptr<sf::RenderWindow> WindowPtr;

namespace SPV
{
class State
{
public:
	State(const std::string& name);
	virtual ~State();

	virtual void OnUpdate() = 0;
	virtual void OnRender() = 0;
	virtual void ProcessEvents(sf::Event& event) = 0;
	virtual bool isExitedState() { return this->isExited; }
	virtual void SetExitedState() { 
		isExited = true;
		SPV_APP_INFO("State exited : {0}", m_StateName);
	}
	virtual std::string GetName() { return this->m_StateName; }

protected:
	std::string m_StateName;
	bool isExited = false;
	WindowPtr window;
	std::shared_ptr<std::vector<std::shared_ptr<SPV::State>>> states;

	virtual void InitState() = 0;
};

typedef std::shared_ptr<std::vector<std::shared_ptr<SPV::State>>> StatesPtr;

} // Namespace SPV