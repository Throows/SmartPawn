#pragma once

#include <SPEngine.h>

class SP_API SPBluePlugin
{
public:
	SPBluePlugin(std::shared_ptr<SP::SPPlugin> data);
	~SPBluePlugin() = default;

	MOVES FindNearestPawnToMove(PawnCoordinates from, PawnCoordinates to);
	std::shared_ptr<SP::SPPlugin> GetData() { return this->api;  };
private:
	std::shared_ptr<SP::SPPlugin> api;

};