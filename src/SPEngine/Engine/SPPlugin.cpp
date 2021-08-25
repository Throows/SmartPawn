#include <iostream>
#include <Engine/SPPLugin.h>

namespace SP
{

	SPPlugin::SPPlugin()
	{
		std::cout << "Plugin created !\n";
	}

	void SPPlugin::SetAction()
	{
		std::cout << "Action success !\n";
	}

	int SPPlugin::GetInfo()
	{
		return 5;
	}
}