#pragma once
#include <Core/pch.hpp>
#include <Core/LocaleText.hpp>

namespace SPV
{

class State;
typedef std::shared_ptr<sf::RenderWindow> WindowPtr;
typedef std::shared_ptr<std::vector<std::shared_ptr<State>>> StatesPtr;
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
	const std::string& GetName() { return this->m_StateName; }

	virtual bool IsInitializedState() { return this->isInitialized; }
	virtual void InitState(std::shared_ptr<SPV::LocaleText>) = 0;

protected:
	std::string m_StateName;
	bool isExited = false;
	bool isInitialized = false;
	WindowPtr window;
	StatesPtr states;
	std::shared_ptr<SPV::LocaleText> m_locale;
};

} // Namespace SPV