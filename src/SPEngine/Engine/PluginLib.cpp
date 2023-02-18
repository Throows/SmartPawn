#include "PluginLib.hpp"
#include <iostream>

namespace SP
{

PluginLib::PluginLib(std::string name)
	: name(name)
{
}

void PluginLib::Update()
{
}

int PluginLib::GetRandomPawn()
{
	return 0;	// TODO
}
int PluginLib::GetFirstPawn()
{
	return 0;	// TODO
}

bool PluginLib::SetAction(int x, int y, int moveType)
{
	if (this->hasPlayed) {
		std::cout << " You have already Played !" << std::endl;
		return false;
	}

	return this->hasPlayed;
}
int PluginLib::GetCoordinatesByMove(int x, int y, int moveType)
{
	return 0;	// TODO
}

} // Namespace SP