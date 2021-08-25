#pragma once

#include <SPEngine.h>

class SP_API SPBluePlugin : public SP::SPPlugin
{
public:
	SPBluePlugin();
	~SPBluePlugin() = default;

	int NotVirtualTest();
};