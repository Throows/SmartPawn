#include "PluginLib.hpp"
#include <stdlib.h>
#include <iostream>

PluginLib::PluginLib(std::string name)
	: name(name)
{
}

Coordinates PluginLib::GetMyRandomPawn()
{
	int random = rand() % this->myPawns.size();
	return this->myPawns[random];
}

Coordinates PluginLib::GetMyFirstPawn()
{
	return this->myPawns.front();
}

Coordinates PluginLib::GetEnnemyRandomPawn()
{
	int random = rand() % this->ennemyPawns.size();
	return this->ennemyPawns[random];
}

Coordinates PluginLib::GetEnnemyFirstPawn()
{
	return this->ennemyPawns.front();
}

bool PluginLib::SetAction(Coordinates pawn, MoveType moveType)
{
	this->pawnToMove = pawn;
	this->moveType = moveType;
	return true;
}

void PluginLib::Reset()
{
	this->pawnToMove = Coordinates{ -1, -1 };
	this->moveType = MoveType::NONE;
}