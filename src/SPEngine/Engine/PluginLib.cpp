#include "PluginLib.hpp"
#include <iostream>

namespace SP
{

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

bool PluginLib::SetAction(int x, int y, MoveType moveType)
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

/*std::string PluginLib::GetStringMove(MoveType move)
{
	switch (move)
	{
	case MoveType::UP:
		return "UP";
		break;
	case MoveType::DOWN:
		return "DOWN";
		break;
	case MoveType::RIGHT:
		return "RIGHT";
		break;
	case MoveType::LEFT:
		return "LEFT";
		break;
	case MoveType::LEFT_TOP_CORNER:
		return "LEFT_TOP_CORNER";
		break;
	case MoveType::LEFT_DOWN_CORNER:
		return "LEFT_DOWN_CORNER";
		break;
	case MoveType::RIGHT_TOP_CORNER:
		return "RIGHT_TOP_CORNER";
		break;
	case MoveType::RIGHT_DOWN_CORNER:
		return "RIGHT_DOWN_CORNER";
		break;
	default:
		return "NONE";
		break;
	}
}*/

void PluginLib::Reset()
{
	this->hasPlayed = false;
	this->pawnX = 0;
	this->pawnY = 0;
	this->moveType = MoveType::NONE;
}

} // Namespace SP