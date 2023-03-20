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
	virtual bool IsExitedState() { return this->isExited; }
	virtual void SetExitedState() { 
		isExited = true;
		SPV_APP_INFO("State exited : {0}", m_StateName);
	}
	virtual std::string GetName() { return this->m_StateName; }

	virtual bool IsInitializedState() { return this->isInitialized; }
	virtual void InitState() { this->isInitialized = true; }

protected:
	std::string m_StateName;
	bool isExited = false;
	bool isInitialized = false;
	WindowPtr window;
	std::shared_ptr<std::vector<std::shared_ptr<SPV::State>>> states;
};

typedef std::shared_ptr<std::vector<std::shared_ptr<SPV::State>>> StatesPtr;

} // Namespace SPV