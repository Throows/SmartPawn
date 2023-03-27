#include "State.hpp"

namespace SPV
{

State::State(StateArgs* args,const std::string& name) 
	: m_stateArgs(args)
	, m_StateName(name)
{
	SPV_APP_TRACE("State {0} Created !", this->m_StateName);
}

State::~State()
{
	SPV_APP_TRACE("State {0} Deleted !", this->m_StateName);
}

} // Namespace SPV
