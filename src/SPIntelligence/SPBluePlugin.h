#pragma once

#include <SPEngine.h>

class SP_API SPBluePlugin
{
public:
	SPBluePlugin(std::shared_ptr<SP::SPData> data);
	~SPBluePlugin() = default;

	MOVES FindNearestPawnToMove(PawnCoordinates from, PawnCoordinates to);
	std::shared_ptr<SP::SPData> GetData() { return this->data;  };
private:
	std::shared_ptr<SP::SPData> data;

};