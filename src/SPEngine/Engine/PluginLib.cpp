#include "PluginLib.hpp"
#include <iostream>

PluginLib::PluginLib(std::string name)
	: name(name)
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
	this->pawnX = x;
	this->pawnY = y;
	this->moveType = moveType;
	return true;
}

void PluginLib::Reset()
{
	this->hasPlayed = false;
	this->pawnX = 0;
	this->pawnY = 0;
	this->moveType = -1;
}