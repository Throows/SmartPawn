#include "State.h"
namespace SP
{
	State::State(const std::string& name)
	{
		this->m_StateName = name;
		SP_APP_TRACE("State Created ! {0}", this->m_StateName);
	}
	State::~State()
	{
		SP_APP_TRACE("State Deleted ! : {0}", this->m_StateName);
	}
}
