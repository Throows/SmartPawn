#pragma once
#include <Core/pch.hpp>
#include <Core/Configuration.hpp>

namespace SPV
{

class State;
typedef std::unique_ptr<sf::RenderWindow> WindowPtr;
typedef std::unique_ptr<SPV::Configuration> ConfigPtr;
typedef std::unique_ptr<std::vector<std::unique_ptr<SPV::State>>> StatesPtr;

struct StateArgs {
	StateArgs()
		: window(nullptr)
		, config(nullptr)
		, states(nullptr) 
	{}
	WindowPtr window;
	ConfigPtr config;
	StatesPtr states;
};
class State
{
public:
	State(StateArgs* args, const std::string& name);
	virtual ~State();

	virtual void OnUpdate(const int& dt) = 0;
	virtual void OnRender() = 0;
	virtual void ProcessEvents(sf::Event& event) = 0;
	virtual bool IsExitedState() { return this->isExited; }
	virtual void SetExitedState() { 
		isExited = true;
		SPV_APP_INFO("State exited : {0}", m_StateName);
	}
	const std::string& GetName() { return this->m_StateName; }

	virtual bool IsInitializedState() { return this->isInitialized; }
	virtual void InitState() = 0;

protected:
	StateArgs* m_stateArgs;
	std::string m_StateName;
	bool isExited = false;
	bool isInitialized = false;
};

} // Namespace SPV