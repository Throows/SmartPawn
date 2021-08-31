#include "State.h"

namespace SP
{
	State::State(const std::string& name)
	{
		this->m_StateName = name;
		SP_APP_TRACE("State {0} Created !", this->m_StateName);
	}

	State::~State()
	{
		SP_APP_TRACE("State {0} Deleted !", this->m_StateName);
	}
}
