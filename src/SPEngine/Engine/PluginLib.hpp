#pragma once
#include <string>
namespace SP
{

enum class MoveType : int
{
	NONE = -1,
	UP = 0,
	DOWN,
	RIGHT,
	LEFT,
	LEFT_TOP_CORNER,
	LEFT_DOWN_CORNER,
	RIGHT_TOP_CORNER,
	RIGHT_DOWN_CORNER
};

class PluginLib
{
public:
	PluginLib(std::string name);
	virtual ~PluginLib() = default;
	std::string GetName() { return this->name; }
	int GetRandomPawn();
	int GetFirstPawn();
	bool SetAction(int x, int y, MoveType moveType);
	void ValidateMove() { this->hasPlayed = true; }
	void Reset();
	MoveType GetPawnMove() { return this->moveType; }
	int GetPawnX() { return this->pawnX; }
	int GetPawnY() { return this->pawnY; }

private:
	bool hasPlayed = false;
	std::string name;
	int pawnX = 0;
	int pawnY = 0;
	MoveType moveType = MoveType::NONE;
	
};

} // Namespace SP